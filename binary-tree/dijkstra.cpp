#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <limits>

using namespace std;
struct Node;
struct Edge;

struct Node {
    int value;
    int in;
    int out;
    vector<Node*> nexts;
    vector<Edge*> edges;
    Node(int v) {
        value = v;
        in = 0;
        out = 0;
    }
};

struct Edge {
    int weight;
    Node *from;
    Node *to;
    Edge(int w, Node *f, Node *t) {
        weight = w;
        from = f;
        to = t;
    }
};

struct Graph {
    unordered_map<int, Node*> nodes;
    unordered_set<Edge*> edges;
};

Node *GetFromHeadMinDistanceNode(const unordered_map<Node*, int>& dist_map, const unordered_set<Node*>& selected_node) {
    Node *min_node = nullptr;
    int min_dist = numeric_limits<int>::max();
    for (auto dist_pair : dist_map) {
        Node *node = dist_pair.first;
        int dist = dist_pair.second;
        if (selected_node.count(node) == 0 && dist < min_dist) {
            min_node = node;
            min_dist = dist;
        }
    }
    return min_node;
}

unordered_map<Node*, int> Dijkstra1(Node *head) {
    unordered_map<Node*, int> dist_map;
    if (head == nullptr) return dist_map;

    unordered_set<Node*> selected_node;
    dist_map[head] = 0;
    Node *min_node = GetFromHeadMinDistanceNode(dist_map, selected_node);
    while (min_node != nullptr) {
        int dist = dist_map[min_node];
        for (Edge *edge : min_node->edges) {
            Node *to_node = edge->to;
            if (dist_map.count(to_node) == 0) {
                dist_map[to_node] = dist + edge->weight;
            } else {
                dist_map[to_node] = min(dist_map[to_node], dist + edge->weight);
            }
        }
        selected_node.insert(min_node);
        min_node = GetFromHeadMinDistanceNode(dist_map, selected_node);
    }
    return dist_map;
}


struct NodeRecord {
    Node *node;
    int dist;
    NodeRecord(Node *n, int d) {
        node = n;
        dist = d;
    }
};

class NodeHeap {
public:
    NodeHeap(int max_size) {
        nodes = new Node*[max_size];
        size = 0;
    }
    ~NodeHeap() {
        delete [] nodes;
    }

    bool IsEmpty() {
        return size == 0;
    }
    void Heapify(int index, int size) {
        int left = (index << 1) + 1;
        while (left < size) {
            int smallest = left + 1 < size && dist_map[nodes[left + 1]] < dist_map[nodes[left]] ? left + 1 : left;
            smallest = dist_map[nodes[smallest]] < dist_map[nodes[index]] ? smallest : index;
            if (smallest == index) break;
            swap(smallest, index);
            index = smallest;
            left = (index << 1) + 1;
        }
    }
    void InsertHeapify(Node *node, int index) {
        int parent_index = (index - 1) / 2;
        while (dist_map[nodes[index]] < dist_map[nodes[parent_index]]) {
            swap(index, parent_index);
            index = parent_index;
            parent_index = (index - 1) / 2;
        }
    }
    void AddOrUpdateOrIgnore(Node *node, int dist) {
        if (in_heap(node)) {
            dist_map[node] = min(dist_map[node], dist);
            if (dist < dist_map[node]) {
                dist_map[node] = dist;
                InsertHeapify(node, heap_index_map[node]);
            }
        }
        if (!is_entered(node)) {
            nodes[size] = node;
            heap_index_map[node] = size;
            dist_map[node] = dist;
            InsertHeapify(node, size++);
        }
    }
    NodeRecord *Pop() {
        NodeRecord *node_record = new NodeRecord(nodes[0], dist_map[nodes[0]]);
        swap(0, size - 1);
        heap_index_map[nodes[size - 1]] = -1;
        dist_map.erase(nodes[size - 1]);
        nodes[size - 1] = nullptr;
        Heapify(0, --size);
        return node_record;
    }

private:
    bool is_entered(Node *node) {
        return heap_index_map.count(node) != 0;
    }
    bool in_heap(Node *node) {
        return is_entered(node) && heap_index_map[node] != -1;
    }
    void swap_node(Node*& a, Node*& b) {
        Node *temp = a;
        a = b;
        b = temp;
    }
    void swap_int(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
    void swap(int index1, int index2) {
        swap_int(heap_index_map[nodes[index1]], heap_index_map[nodes[index2]]);
        swap_node(nodes[index1], nodes[index2]);
    }

    Node **nodes;
    unordered_map<Node*, int> heap_index_map;
    unordered_map<Node*, int> dist_map;
    int size;
};

unordered_map<Node*, int> Dijkstra2(Node *head, int max_heap_size) {
    NodeHeap *node_heap = new NodeHeap(max_heap_size);
    node_heap->AddOrUpdateOrIgnore(head, 0);
    unordered_map<Node*, int> result;
    while (!node_heap->IsEmpty()) {
        NodeRecord *node_record = node_heap->Pop();
        Node *cur = node_record->node;
        int dist = node_record->dist;
        for (Edge *edge : cur->edges) {
            node_heap->AddOrUpdateOrIgnore(edge->to, dist + edge->weight);
        }
        result[cur] = dist;
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
        Edge *edge = new Edge(weight, from_node, to_node);
        from_node->nexts.push_back(to_node);
        from_node->out++;
        to_node->in++;
        from_node->edges.push_back(edge);
        graph->edges.insert(edge);
    }
    return graph;
}

void DestroyGraph(Graph *graph) {
    for (auto pair : graph->nodes) {
        delete pair.second;
        pair.second = nullptr;
    }
    for (auto edge : graph->edges) {
        delete edge;
        edge = nullptr;
    }
    delete graph;
    graph = nullptr;
}

Graph *GenerateExampleGraph() {
    vector<vector<int> > matrix1 = {
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
    vector<vector<int> > matrix2 = {
            { 50,   'A', 'B' },
            { 100,  'A', 'E' },
            { 3,    'A', 'C' },
            { 10,   'B', 'D' },
            { 10,   'D', 'B' },
            { 10,   'B', 'F' },
            { 7,    'C', 'D' },
            { 70,   'C', 'F' },
            { 50,   'A', 'B' },
            { 20,   'D', 'E' },
            { 5,    'E', 'F' },

    };
//    return GenerateGraph(matrix1);
    return GenerateGraph(matrix2);
}

int main() {
    Graph *graph = GenerateExampleGraph();
    auto iter = graph->nodes.begin();
    iter++;
    iter++;
    Node *head = iter->second;

    unordered_map<Node*, int> dist_map = Dijkstra1(head);
    cout << "Dijkstra1:" << endl;
    for (auto dist_pair : dist_map) {
        cout << char(head->value) << "-->" << char(dist_pair.first->value) << ": " << dist_pair.second << endl;
    }

    dist_map = Dijkstra2(head, 10);
    cout << "\nDijkstra2:" << endl;
    for (auto dist_pair : dist_map) {
        cout << char(head->value) << "-->" << char(dist_pair.first->value) << ": " << dist_pair.second << endl;
    }
    DestroyGraph(graph);

    return 0;
}
