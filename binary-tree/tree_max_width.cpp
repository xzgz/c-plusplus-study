#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node {
    int value;
    Node *left;
    Node *right;
    Node(int v) {
        value = v;
        left = nullptr;
        right = nullptr;
    }
};

int MaxWidthUseMap(Node *head) {
    if (head == nullptr) return 0;

    queue<Node*> q;
    unordered_map<Node*, int> level_map;
    q.push(head);
    level_map[head] = 1;
    int cur_level = 1;
    int cur_level_nodes = 1;
    int max_level_nodes = 0;
    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        int cur_node_level = level_map[cur];
        if (cur->left != nullptr) {
            q.push(cur->left);
            level_map[cur->left] = cur_node_level + 1;
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
            level_map[cur->right] = cur_node_level + 1;
        }
        if (cur_node_level == cur_level) {
            cur_level_nodes++;
        } else {
            max_level_nodes = max(max_level_nodes, cur_level_nodes);
            cur_level++;
            cur_level_nodes = 1;
        }
    }
    max_level_nodes = max(max_level_nodes, cur_level_nodes);
    return max_level_nodes;
}

int MaxWidthNoMap(Node *head) {
    if (head == nullptr) return 0;

    queue<Node*> q;
    unordered_map<Node*, int> level_map;
    q.push(head);
    Node *cur_end = head;
    Node *next_end = nullptr;
    int max_level_nodes = 0;
    int cur_level_nodes = 1;
    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        if (cur->left != nullptr) {
            q.push(cur->left);
            next_end = cur->left;
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
            next_end = cur->right;
        }
        cur_level_nodes++;
        if (cur == cur_end) {
            max_level_nodes = max(max_level_nodes, cur_level_nodes);
            cur_level_nodes = 0;
            cur_end = next_end;
        }
    }
    return max_level_nodes;
}

Node *ConstructBinaryTree() {
    Node *n0 = new Node(3);
    Node *n1 = new Node(5);
    Node *n2 = new Node(6);
    Node *n3 = new Node(1);
    Node *n4 = new Node(9);
    Node *n5 = new Node(1);
    Node *n6 = new Node(2);
    Node *n7 = new Node(2);
    Node *n8 = new Node(-1);
    Node *n9 = new Node(0);
    Node *n10 = new Node(10);
    Node *n11 = new Node(8);
    n0->left = n1;
    n0->right = n2;
    n1->left = n3;
    n1->right = n4;
    n2->left = n5;
    n2->right = n6;
    n3->right = n7;
    n4->left = n8;
    n4->right = n9;
    n6->left = n10;
    n6->right = n11;
    return n0;
}

int main() {
    Node *head = ConstructBinaryTree();
    int max_width1 = MaxWidthUseMap(head);
    int max_width2 = MaxWidthNoMap(head);
    cout << "max_width1: " << max_width1 << "\tmax_width2: " << max_width2 << endl;

    return 0;
}
