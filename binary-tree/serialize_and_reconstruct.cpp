#include <iostream>
#include <queue>
#include <stack>

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

void Pre(Node *head, queue<string>& ans) {
    if (head == nullptr) {
        ans.push("");
    } else {
        ans.push(to_string(head->value));
        Pre(head->left, ans);
        Pre(head->right, ans);
    }
}

queue<string> PreSerialize(Node *head) {
    queue<string> ans;
    Pre(head, ans);
    return ans;
}

Node *PreBuild(queue<string>& pre_q) {
    string val = pre_q.front();
    pre_q.pop();
    if (val == "") return nullptr;
    Node *head = new Node(stoi(val));
    head->left = PreBuild(pre_q);
    head->right = PreBuild(pre_q);
    return head;
}

Node *BuildByPreQueue(queue<string>& pre_q) {
    if (pre_q.empty()) return nullptr;
    return PreBuild(pre_q);
}

queue<string> LevelSerialize(Node *head) {
    queue<string> ans;
    if (head == nullptr) {
        ans.push("");
    } else {
        ans.push(to_string(head->value));
        queue<Node*> node_q;
        node_q.push(head);
        while (!node_q.empty()) {
            head = node_q.front();
            node_q.pop();
            if (head->left != nullptr) {
                ans.push(to_string(head->left->value));
                node_q.push(head->left);
            } else {
                ans.push("");
            }
            if (head->right != nullptr) {
                ans.push(to_string(head->right->value));
                node_q.push(head->right);
            } else {
                ans.push("");
            }
        }
    }
    return ans;
}

Node *GenerateNode(string& v) {
    if (v == "") return nullptr;
    return new Node(stoi(v));
}

Node *BuildbyLevelQueue(queue<string>& level_q) {
    if (level_q.empty()) return nullptr;

    Node *head = GenerateNode(level_q.front());
    level_q.pop();
    queue<Node*> node_q;
    if (head != nullptr) {
        node_q.push(head);
    }
    Node *node = nullptr;
    while (!node_q.empty()) {
        node = node_q.front();
        node_q.pop();
        node->left = GenerateNode(level_q.front());
        level_q.pop();
        node->right = GenerateNode(level_q.front());
        level_q.pop();
        if (node->left != nullptr) {
            node_q.push(node->left);
        }
        if (node->right != nullptr) {
            node_q.push(node->right);
        }
    }
    return head;
}

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
    Node *head = ConstructBinaryTree();
    PrintTreePreOrder(head);
    queue<string> q = PreSerialize(head);
    head = BuildByPreQueue(q);
    PrintTreePreOrder(head);

    q = LevelSerialize(head);
    head = BuildbyLevelQueue(q);
    PrintTreePreOrder(head);

    PrintTreePerfect(head);

    return 0;
}
