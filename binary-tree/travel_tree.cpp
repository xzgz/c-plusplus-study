#include <iostream>
#include <stack>
#include <queue>

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

void PrintTreePreOrder(Node *head) {
    cout << "pre-order:" << endl;
    if (head != nullptr) {
        stack<Node*> s;
        s.push(head);
        while (!s.empty()) {
            head = s.top();
            s.pop();
            cout << head->value << " ";
            if (head->right != nullptr) {
                s.push(head->right);
            }
            if (head->left != nullptr) {
                s.push(head->left);
            }
        }
    }
    cout << endl;
}

void PrintTreePosOrder1(Node *head) {
    cout << "pos-order1:" << endl;
    if (head != nullptr) {
        stack<Node*> s1;
        stack<Node*> s2;
        s1.push(head);
        while (!s1.empty()) {
            head = s1.top();
            s1.pop();
            s2.push(head);
            if (head->left != nullptr) {
                s1.push(head->left);
            }
            if (head->right != nullptr) {
                s1.push(head->right);
            }
        }
        while (!s2.empty()) {
            head = s2.top();
            s2.pop();
            cout << head->value << " ";
        }
    }
    cout << endl;
}

void PrintTreeInOrder(Node *head) {
    cout << "in-order:" << endl;
    if (head != nullptr) {
        stack<Node*> s;
        while (!s.empty() || head != nullptr) {
            if (head != nullptr) {
                s.push(head);
                head = head->left;
            } else {
                head = s.top();
                s.pop();
                cout << head->value << " ";
                head = head->right;
            }
        }
    }
    cout << endl;
}

void PrintTreePosOrder2(Node *h) {
    cout << "pos-order2:" << endl;
    if (h != nullptr) {
        Node *c = nullptr;
        stack<Node*> s;
        s.push(h);
        while (!s.empty()) {
            c = s.top();
            if (c->left != nullptr && h != c->left && h != c->right) {
                s.push(c->left);
            } else if (c->right != nullptr && h != c->right) {
                s.push(c->right);
            } else {
                cout << s.top()->value << " ";
                s.pop();
                h = c;
            }
        }
    }
    cout << endl;
}

void PrintTreeLevelOrder(Node *head) {
    cout << "level-order:" << endl;
    if (head == nullptr) return;

    queue<Node*> q;
    q.push(head);
    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        cout << cur->value << " ";
        if (cur->left != nullptr) {
            q.push(cur->left);
        }
        if (cur->right != nullptr) {
            q.push(cur->right);
        }
    }
    cout << endl;
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
    PrintTreePreOrder(head);
    PrintTreePosOrder1(head);
    PrintTreePosOrder2(head);
    PrintTreeInOrder(head);
    PrintTreeLevelOrder(head);

    return 0;
}
