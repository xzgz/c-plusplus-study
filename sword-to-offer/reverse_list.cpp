#include <bits/stdc++.h>

using namespace std;

struct ListNode {
  ListNode(int data, ListNode *node = NULL)
          : data(data), next(node) {}
  int data;
  ListNode *next;
};

ListNode *ReverseList(ListNode *pHead) {
  if (pHead == NULL || pHead->next == NULL) return pHead;
  ListNode *next = pHead->next;
  pHead->next = NULL;
  ListNode *new_head = ReverseList(next);
  next->next = pHead;

  return new_head;
}

ListNode *ReverseList2(ListNode *pHead) {
  ListNode *new_list = NULL;
  while (pHead != NULL) {
	ListNode *next = pHead->next;
    pHead->next = new_list;
	new_list = pHead;
    pHead = next;
  }

  return new_list;
}

void OutputList(ListNode *head) {
  while (head != NULL) {
    cout << head->data << endl;
    head = head->next;
  }
}

void DeleteList(ListNode *head) {
  while (head != NULL) {
    ListNode *temp = head;
    head = head->next;
    delete temp;
  }
}

int main() {
  ListNode *nd1 = new ListNode(1);
  ListNode *nd2 = new ListNode(2, nd1);
  ListNode *nd3 = new ListNode(3, nd2);
  ListNode *nd4 = new ListNode(4, nd3);

  OutputList(nd4);
  cout << "**************\n";
  ListNode *new_head = ReverseList(nd4);
  OutputList(new_head);
  cout << "**************\n";
  new_head = ReverseList2(new_head);
  OutputList(new_head);

  DeleteList(nd4);
}
