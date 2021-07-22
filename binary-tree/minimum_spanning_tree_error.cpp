#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;
struct Node;
struct Edge;

struct Node {
    int value;
    int in;
    int out;
    vector<Node*> nexts;
    vector<Edge*> edges;
    Node() {}
    Node(int v) {
        value = v;
        in = 0;
        out = 0;
    }
    friend bool operator==(const Node& a, const Node& b) {
        return a.value == b.value;
    }
//    friend bool operator!=(const Node& a, const Node& b) {
//        return a.value != b.value;
//    }
//    bool operator==(const Node& b) {
//        return this->value == b.value;
//    }
    bool operator!=(const Node& b) {
        return this->value != b.value;
    }
};

struct Edge {
    int weight;
    Node& from;
    Node& to;
    Edge(const Edge& e) : from(e.from), to(e.to) {
        weight = e.weight;
    }
    Edge(int w, Node& f, Node& t) : from(f), to(t) {
        weight = w;
    }
//    Node *from;
//    Node *to;
//    Edge(int w, Node *f, Node *t) {
//        weight = w;
//        from = f;
//        to = t;
//    }
    friend bool operator==(const Edge& a, const Edge& b) {
        return a.weight == b.weight && a.from == b.from && a.to == b.to;
    }
    friend bool operator<(const Edge& a, const Edge& b) {
        if (a.weight == b.weight) {
            return a.from.value > b.from.value;
        } else {
            return a.weight < b.weight;
        }
    }
    Edge& operator=(Edge&& e) noexcept {
        weight = e.weight;
        from = e.from;
        to = e.to;
        return *this;
    }
};

struct Graph {
    unordered_map<int, Node*> nodes;
//    unordered_set<Edge> edges;  //error: no match for call to (const std::hash<Edge>) (const Edge&)
    unordered_set<Edge*> edges;
};

namespace std {
    template <>
    class hash<Node> {
    public:
        size_t operator()(const Node& node) const {
            size_t h = hash<int>()(node.value);
            return h;
        }
    };

    template <>
    class hash<Edge> {
    public:
        size_t operator()(const Edge& edge) const {
            size_t h1 = hash<int>()(edge.weight);
            size_t h2 = hash<int>()(edge.from.value);
            size_t h3 = hash<int>()(edge.to.value);
            return h1 ^ (h2 << 1) ^ (h3 << 1);
        }
    };
}

class UnionFind {
public:
//    UnionFind() {}
    void MakeSet(const unordered_map<int, Node*>& nodes) {
//        for (unordered_map<int, Node*>::const_iterator iter = nodes.begin(); iter != nodes.end(); ++iter) {
//            Node *node = iter->second;
//            parents[*node] = *node;
//            map_size[*node] = 1;
//        }
        for (auto pair : nodes) {
            Node *node = pair.second;
            parents[*node] = *node;
            map_size[*node] = 1;
        }
    }
    Node FindFather(Node node) {
        stack<Node > path;
        while (node != parents[node]) {
            path.push(node);
            node = parents[node];
        }
        while (!path.empty()) {
            parents[path.top()] = node;
            path.pop();
        }
        return node;
    }
    bool IsSameSet(const Node *a, const Node *b) {
        return FindFather(*a) == FindFather(*b);
    }
    void Union(const Node *a, const Node *b) {
        if (a == nullptr || b == nullptr) return;

        Node a_head = FindFather(*a);
        Node b_head = FindFather(*b);
        if (a_head != b_head) {
            int a_set_size = map_size[a_head];
            int b_set_size = map_size[b_head];
            Node big = a_set_size > b_set_size ? a_head : b_head;
            Node small = big == a_head ? b_head : a_head;
            parents[small] = big;
            map_size[big] = a_set_size + b_set_size;
            map_size.erase(small);
        }
    }

private:
    unordered_map<Node, Node > parents;
    unordered_map<Node, int> map_size;
};

auto CmpEdge = [](const Edge& a, const Edge& b) {
    return a.weight > b.weight;
};

unordered_set<Edge> KruskalMst(Graph *graph) {
    UnionFind union_find = UnionFind();
    union_find.MakeSet(graph->nodes);
    priority_queue<Edge, vector<Edge>, decltype(CmpEdge)> pq(CmpEdge);
    for (Edge *edge : graph->edges) {
        pq.push(*edge);
    }
    unordered_set<Edge> result;

    while (!pq.empty()) {
        const Edge& top = pq.top(); pq.pop();
        if (!union_find.IsSameSet(&top.from, &top.to)) {
            result.insert(top);
            union_find.Union(&top.from, &top.to);
        }
    }
    return result;
}

set<Edge> PrimMst(Graph *graph) {
    priority_queue<Edge, vector<Edge>, decltype(CmpEdge)> pq(CmpEdge);
    unordered_set<const Node*> node_set;
    unordered_set<Edge> edge_set;
    set<Edge> result;
    for (auto iter = graph->nodes.begin(); iter != graph->nodes.end(); ++iter) {
        Node *node = iter->second;
        if (node_set.count(node) == 0) {
            node_set.insert(node);
            for (Edge *edge : node->edges) {
                if (edge_set.count(*edge) == 0) {
                    edge_set.insert(*edge);
                    pq.push(*edge);
                }
            }
            while (!pq.empty()) {
                int size = pq.size();
                const Edge& edge_ref = pq.top();
                Edge edge = edge_ref;
                pq.pop();
                const Node *to_node = &edge.to;
                if (node_set.count(to_node) == 0) {
                    node_set.insert(to_node);
                    result.insert(edge);
                    for (auto e : to_node->edges) {
                        if (edge_set.count(*e) == 0) {
                            edge_set.insert(*e);
                            pq.push(*e);
                        }
                    }
                }
            }
        }
        break;
    }
    return result;
}

Graph *GenerateGraph(vector<vector<int> > matrix) {
    Graph *graph = new Graph();
    for (int i = 0; i < matrix.size(); ++i) {
        int weight =  matrix[i][0];
        int from = matrix[i][1];
        int to = matrix[i][2];
        if (graph->nodes.count(from) == 0) {
            graph->nodes[from] = new Node(from);
        }
        if (graph->nodes.count(to) == 0) {
            graph->nodes[to] = new Node(to);
        }
        Node *from_node = graph->nodes[from];
        Node *to_node = graph->nodes[to];
        Edge *edge = new Edge(weight, *from_node, *to_node);
        from_node->nexts.push_back(to_node);
        from_node->out++;
        to_node->in++;
        if (from_node->value == 'A') {
            cout << edge->weight << endl;
        }
        from_node->edges.push_back(edge);
        graph->edges.insert(edge);
    }
    return graph;
}

Graph *GenerateExampleGraph() {
    vector<vector<int> > matrix = {
            {7, 'A', 'B'},
            {7, 'B', 'A'},
            {5, 'A', 'D'},
            {5, 'D', 'A'},
            {8, 'B', 'C'},
            {8, 'C', 'B'},
            {7, 'B', 'E'},
            {7, 'E', 'B'},
            {5, 'C', 'E'},
            {5, 'E', 'C'},
            {9, 'B', 'D'},
            {9, 'D', 'B'},
            {15, 'D', 'E'},
            {15, 'E', 'D'},
            {6, 'D', 'F'},
            {6, 'F', 'D'},
            {8, 'F', 'E'},
            {8, 'E', 'F'},
            {11, 'F', 'G'},
            {11, 'G', 'F'},
            {9, 'E', 'G'},
            {9, 'G', 'E'},
    };
    return GenerateGraph(matrix);
}


int main() {
    Graph *graph = GenerateExampleGraph();
//    unordered_set<Edge> unordered_mst = KruskalMst(graph);
//    cout << "KruskalMst:" << endl;
//    for (auto e : unordered_mst) {
//        cout << "from " << char(e.from.value) << " to " << char(e.to.value) << " w: " << e.weight << endl;
//    }
    set<Edge> ordered_mst = PrimMst(graph);
    cout << "PrimMst:" << endl;
    for (auto e : ordered_mst) {
        cout << "from " << char(e.from.value) << " to " << char(e.to.value) << " w: " << e.weight << endl;
    }

    return 0;
}
