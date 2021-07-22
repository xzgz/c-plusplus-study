#include <bits/stdc++.h>

using namespace std;

// refer to: https://blog.csdn.net/hh66__66hh/article/details/82939450
// refer to: https://blog.csdn.net/qq_39119348/article/details/100847674

struct BiTNode {
  int value;
  BiTNode *parent;
  BiTNode *lchild;
  BiTNode *rchild;
  int pos;
  BiTNode(int value, BiTNode *parent, BiTNode *lchild, BiTNode *rchild)
		  : value(value), pos(0), parent(parent), lchild(lchild), rchild(rchild) {}
};

void SearchInOrder(BiTNode *root) {
  if (root == NULL) return;
  // 只有一个根节点
  if (root->lchild == NULL && root->rchild == NULL) {
    cout << root->value << " ";
    return;
  }
  BiTNode *pre = root->parent;
  while (true) {
    // 遍历左节点
	if (root->lchild != NULL && root->parent == pre) {
	  pre = root;
	  root = root->lchild;
	}
	// 遍历到叶子节点，向上
	else if (root->lchild == NULL && root->rchild == NULL) {
	  cout << root->value << " ";
	  pre = root;
	  root = root->parent;
	}
	// 从左节点回来，遍历当前节点不为空的右节点
	else if (root->lchild == pre && root->rchild != NULL) {
	  cout << root->value << " ";
	  pre = root;
	  root = root->rchild;
	}
	// 从左节点回来，当前节点的右节点为空，且该节点不是根节点
	else if (root->lchild == pre && root->rchild == NULL && root->parent != NULL) {
	  cout << root->value << " ";
	  pre = root;
	  root = root->parent;
	}
	// 当前节点没有左节点但有右节点，且右节点没有被遍历过
	else if (root->lchild == NULL && root->rchild != NULL && root->rchild != pre) {
	  cout << root->value << " ";
	  pre = root;
	  root = root->rchild;
	}
	// 遍历结束条件
	else if (root->rchild != NULL && root->rchild == pre && root->parent == NULL) {
	  // 从右节点回来，且当前节点为根节点
	  return;
	}
	// 从左节点回来，当前节点的右节点为空，且当前节点为根节点
	else if (root->lchild == pre && root->rchild == NULL && root->parent == NULL) {
	  cout << root->value << " ";
	  return;
	}
	// 从右节点向上
	else if (root->rchild == pre) {
	  pre = root;
	  root = root->parent;
	}
  }
}

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

int main() {
  BiTNode *root = ConstructTree();
  SearchInOrder(root);

  return 0;
}
