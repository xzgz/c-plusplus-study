#include <bits/stdc++.h>

using namespace std;

// refer to: https://blog.csdn.net/hh66__66hh/article/details/82939450
// refer to: https://blog.csdn.net/wildbeast_/article/details/79006348

struct BiTNode {
  int value;
  BiTNode *parent;
  BiTNode *lchild;
  BiTNode *rchild;
  int pos;
  BiTNode(int value, BiTNode *parent, BiTNode *lchild, BiTNode *rchild)
		  : value(value), pos(0), parent(parent), lchild(lchild), rchild(rchild) {}
};

BiTNode *ConstructTree() {
  BiTNode *root = new BiTNode(4, NULL, NULL, NULL);
  BiTNode *node7 = new BiTNode(7, root, NULL, NULL);
  BiTNode *node2 = new BiTNode(2, root, NULL, NULL);
  BiTNode *node9 = new BiTNode(9, node7, NULL, NULL);
  BiTNode *node1 = new BiTNode(1, node2, NULL, NULL);
  BiTNode *node5 = new BiTNode(5, node2, NULL, NULL);
  BiTNode *node6 = new BiTNode(6, node5, NULL, NULL);
  root->lchild = node7;
  root->rchild = node2;
  node7->rchild = node9;
  node2->lchild = node1;
  node2->rchild = node5;
  node5->lchild = node6;

  return root;
}

/*
题目：
给定一个二叉树，任意两个节点之间必然是有一条路径相通的，假定父节点和它的孩子
节点的距离为单位1，求二叉树中相距最远的两个节点间的路径长度
 */
int LongestPath(BiTNode *root, int& lp) {
  if (root == NULL || root->lchild == NULL && root->rchild == NULL) return 0;

  int len_left = 0, len_right = 0;
  if (root->lchild != NULL) {
    len_left = LongestPath(root->lchild, lp) + 1;
  }
  if (root->rchild != NULL) {
    len_right = LongestPath(root->rchild, lp) + 1;
  }
  int sum = len_left + len_right;
  sum > lp ? lp = sum : 0;

  return len_left > len_right ? len_left : len_right;
}

/*
题目：
给定一个二叉树，任意两个节点之间必然是有一条路径相通的，求两个节点
之间路径上的所有节点(包括这两个节点)的值之和的最大值。
 */
int MaxSumValuePath(BiTNode *root, int& max_value) {
  if (root == NULL) return max_value;
  if (root->lchild == NULL && root->rchild == NULL) return root->value;

  int sum_left = INT_MIN, sum_right = INT_MIN;
  if (root->lchild != NULL) {
    sum_left = MaxSumValuePath(root->lchild, max_value);
  }
  if (root->rchild != NULL) {
    sum_right = MaxSumValuePath(root->rchild, max_value);
  }
  if (sum_left == INT_MIN) {
    sum_left = root->value;
    sum_right += root->value;
  }
  else if (sum_right == INT_MIN) {
    sum_left += root->value;
    sum_right = root->value;
  }
  else {
    sum_left += root->value;
    sum_right += root->value;
  }
  int sum = sum_left + sum_right - root->value;
  sum > max_value ? max_value = sum : 0;

  return sum_left > sum_right ? sum_left : sum_right;
}

int main() {
  BiTNode *root = ConstructTree();

  int longest_path = 0;
  LongestPath(root, longest_path);
  cout << longest_path << endl;

  int max_value = INT_MIN;
  MaxSumValuePath(root, max_value);
  cout << max_value << endl;
  cout << INT_MIN << endl;
  cout << -INT_MIN << endl;
  cout << INT_MAX << endl;

  return 0;
}
