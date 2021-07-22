#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

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

void BFS(Node *node) {
    if (node == nullptr) return;
    queue<Node*> q;
    unordered_set<Node*> s;
    q.push(node);
    s.insert(node);
    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        cout << char(cur->value) << endl;
        for (Node *next : cur->nexts) {
            if (s.count(next) == 0) {
                q.push(next);
                s.insert(next);
            }
        }
    }
}

void DFS(Node *node) {
    if (node == nullptr) return;
    stack<Node*> stack;
    unordered_set<Node*> set;
    stack.push(node);
    set.insert(node);
    cout << char(node->value) << endl;
    while (!stack.empty()) {
        Node *cur = stack.top();
        stack.pop();
        for (Node *next : cur->nexts) {
            if (set.count(next) == 0) {
                stack.push(cur);
                stack.push(next);
                set.insert(next);
                cout << char(next->value) << endl;
                break;
            }
        }
    }
}

vector<Node*> TopologySort(Graph *graph) {
    unordered_map<Node*, int> in_map;
    queue<Node*> zero_in_queue;
    for (unordered_map<int, Node*>::iterator iter = graph->nodes.begin(); iter != graph->nodes.end(); ++iter) {
        Node *node = iter->second;
        in_map[node] = node->in;
        if (node->in == 0) {
            zero_in_queue.push(node);
        }
    }

    vector<Node*> result;
    while (!zero_in_queue.empty()) {
        Node *cur = zero_in_queue.front();
        zero_in_queue.pop();
        result.push_back(cur);
        for (Node *next : cur->nexts) {
            in_map[next]--;
            if (in_map[next] == 0) {
                zero_in_queue.push(next);
            }
        }
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

Graph *GenerateExampleNoCircleGraph() {
    vector<vector<int> > matrix = {
            {7, 'A', 'B'},
            {5, 'D', 'A'},
            {8, 'C', 'B'},
            {7, 'B', 'E'},
            {5, 'C', 'E'},
            {9, 'D', 'B'},
            {15, 'D', 'E'},
            {6, 'F', 'D'},
            {8, 'F', 'E'},
            {11, 'F', 'G'},
            {9, 'G', 'E'},
    };
    return GenerateGraph(matrix);
}

int main() {
    unordered_map<Node*, int> in_map;
    Node *n = new Node(6);
    in_map[n] = 10;
    in_map[n]--;
    cout << in_map[n] << endl;

    Graph *graph = GenerateExampleGraph();
    cout << "BFS:" << endl;
    BFS(graph->nodes.begin()->second);
    cout << "DFS:" << endl;
    DFS(graph->nodes.begin()->second);
    DestroyGraph(graph);
//    unordered_set<Edge*>::iterator it = g.edges.begin();
//    cout << (*graph->edges.begin())->weight << endl;

    graph = GenerateExampleNoCircleGraph();
    cout << "\nBFS:" << endl;
    BFS(graph->nodes.begin()->second);
    vector<Node*> tr = TopologySort(graph);
//    DestroyGraph(graph);
    cout << "TopologySort:" << endl;
    for (Node *node : tr) {
        cout << char(node->value) << endl;
    }
    DestroyGraph(graph);
}
