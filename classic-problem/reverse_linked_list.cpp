#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    Node *next;
    Node(int val) {
        value = val;
    }
};

struct DoubleNode {
    int value;
    DoubleNode *last;
    DoubleNode *next;
    DoubleNode(int val) {
        value = val;
    }
};

void PrintLinkedList(Node *head) {
    while (head != nullptr) {
        cout << head->value << "-->";
        head = head->next;
    }
    cout << "nullptr" << endl;
}

void PrintDoubleLinkedList(DoubleNode *head) {
    DoubleNode *last_node = nullptr;
    while (head != nullptr) {
        if (head->next == nullptr) {
            last_node = head;
        }
        cout << head->value << "-->";
        head = head->next;
    }
    cout << "nullptr" << endl;

    while (last_node != nullptr) {
        cout << last_node->value << "-->";
        last_node = last_node->last;
    }
    cout << "nullptr" << endl;
}

Node *ReverseLinkedList(Node *head) {
    Node *pre = nullptr;
    Node *next = nullptr;
    while (head != nullptr) {
        next = head->next;
        head->next = pre;
        pre = head;
        head = next;
    }
    return pre;
}

DoubleNode *ReverseDoubleLinkedList(DoubleNode *head) {
    DoubleNode *pre = nullptr;
    DoubleNode *next = nullptr;
    while (head != nullptr) {
        next = head->next;
        head->next = pre;
        head->last = next;
        pre = head;
        head = next;
    }
    return pre;
}

void TestReverseLinkedList() {
    cout << "TestReverseLinkedList:" << endl;
    int length = 12;
    Node *head = new Node(0);
    Node *node = head;
    for (int i = 1; i <= length; ++i) {
        node->next = new Node(i);
        node = node->next;
    }
    node->next = nullptr;

    PrintLinkedList(head);
    Node *reverse_head = ReverseLinkedList(head);
    PrintLinkedList(reverse_head);

    while (head != nullptr) {
        node = head->next;
        delete head;
        head = node;
    }
}

void TestReverseDoubleLinkedList() {
    cout << "TestReverseDoubleLinkedList:" << endl;
    int length = 17;
    DoubleNode *head = new DoubleNode(0);
    head->last = nullptr;
    DoubleNode *last = head;
    DoubleNode *node = head;
    for (int i = 1; i <= length; ++i) {
        node->next = new DoubleNode(i);
        node = node->next;
        node->last = last;
        last = node;
    }
    node->next = nullptr;

    PrintDoubleLinkedList(head);
    DoubleNode *reverse_head = ReverseDoubleLinkedList(head);
    PrintDoubleLinkedList(reverse_head);

    while (head != nullptr) {
        node = head->next;
        delete head;
        head = node;
    }
}

int main() {
    TestReverseLinkedList();
    TestReverseDoubleLinkedList();

    return 0;
}
