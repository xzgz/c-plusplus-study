#include <bits/stdc++.h>

using namespace std;

// refer to: https://www.cnblogs.com/edisonchou/p/4769164.html

struct SingleLinkNode {
  int val;
  SingleLinkNode *next;
  SingleLinkNode(int val, SingleLinkNode *next = nullptr) : val(val), next(next) {}
};

SingleLinkNode *DeleteLastkNode(SingleLinkNode *head, int k) {
  if (head == nullptr || k < 1) return head;

  SingleLinkNode *ahead = head;
  SingleLinkNode *behind = head;
  if (k == 1) {    // remove the last node
    if (head->next == nullptr) {  // link only has one node
      delete head;
      head = nullptr;
    } else {
      while (ahead->next != nullptr) {
        behind = ahead;
        ahead = ahead->next;
      }
      behind->next = nullptr;
      delete ahead;
      ahead = nullptr;
    }
  } else {
    for (int i = 0; i < k; ++i) {
      if (ahead->next != nullptr) {
        ahead = ahead->next;
      } else if (ahead->next==nullptr && i==k-1) {  // remove the first node
        SingleLinkNode *temp = head;
        head = head->next;
        delete temp;
        temp = nullptr;
      }
      else {
        return head;
      }
    }
    while (ahead != nullptr) {
      ahead = ahead->next;
      behind = behind->next;
    }
    behind->next = behind->next->next;
    delete behind->next;
    behind->next = nullptr;
  }

  return head;
}
