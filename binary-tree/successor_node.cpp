#include <iostream>

using namespace std;

struct Node {
    int value;
    Node *parent;
    Node *left;
    Node *right;
    Node(int v) {
        value = v;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

Node *GetLeftMost(Node *node) {
    if (node == nullptr) return node;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/*
 * 返回一个二叉树中某个节点的后继节点。
 * 后继节点指的是二叉树的中序遍历中，在一个节点之后被遍历的节点。
 */
Node *GetSuccessorNode(Node *node) {
    if (node == nullptr) return node;
    if (node->right != nullptr) {
        return GetLeftMost(node->right);
    } else {
        Node *parent = node->parent;
        while (parent != nullptr && parent->left != node) {
            node = parent;
            parent = node->parent;
        }
        return parent;
    }
}

Node *ConstructBinaryTreeWithParent() {
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
    n1->parent = n0;
    n2->parent = n0;

    n1->left = n3;
    n1->right = n4;
    n3->parent = n1;
    n4->parent = n1;

    n2->left = n5;
    n2->right = n6;
    n5->parent = n2;
    n6->parent = n2;

    n3->right = n7;
    n7->parent = n3;

    n4->left = n8;
    n4->right = n9;
    n8->parent = n4;
    n9->parent = n4;

    n6->left = n10;
    n6->right = n11;
    n10->parent = n6;
    n11->parent = n6;

    return n0;
}

string GetSpace(int count) {
    string space = " ";
    string v = "";
    for (int i = 0; i < count; ++i) v += space;
    return v;
}

void PrintTreePerfect(Node *head, int height, string to, int len) {
    if (head == nullptr) return;
    PrintTreePerfect(head->right, height + 1, "v", len);
    string val = to + to_string(head->value) + to;
    int len_m = val.length();
    int len_l = (len - len_m) / 2;
    int len_r = len - len_l - len_m;
    val = GetSpace(len_l) + val + GetSpace(len_r);
    cout << GetSpace(height * len) + val << endl;
    PrintTreePerfect(head->left, height + 1, "^", len);
}

void PrintTreePerfect(Node *head) {
    cout << "binary tree in counter-clockwise format:" << endl;
    PrintTreePerfect(head, 0, "H", 17);
}

int main() {
    Node *head = ConstructBinaryTreeWithParent();
    PrintTreePerfect(head);
    Node *node = head->right->right->right;
    Node *successor = GetSuccessorNode(node);
    cout << "node->value: " << node->value;
    if (successor == nullptr) {
        cout << "\tsuccessor->value: nullptr" << endl;
    } else {
        cout << "\tsuccessor->value: " << successor->value << endl;
    }
}
