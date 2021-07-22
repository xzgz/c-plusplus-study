#include <bits/stdc++.h>
#include "include/tree.h"

using namespace std;

// refer to: https://blog.csdn.net/monster_ii/article/details/82115772

int LevelOrder(BiTNode *root) {
  if (root == NULL) return 0;

  int depth = 0;
  std::queue<BiTNode *> q;
  BiTNode *front;
  q.push(root);
  while (!q.empty())
  {
    ++depth;
    cout << "\ndepth " << depth << ": ";
    int level_num = q.size();
    for (int i = 0; i < level_num; ++i) {
      front = q.front();
      q.pop();
      cout << front->value << " ";

      if (front->lchild)
        q.push(front->lchild);

      if (front->rchild)
        q.push(front->rchild);
    }
  }

  return depth;
}

void PreOrder(const BiTNode *root) {
  if (root == NULL) {
    cout << "# ";
    return;
  }
  cout << root->value << " ";        //输出根节点的值
  PreOrder(root->lchild);            //前序访问左子树
  PreOrder(root->rchild);            //前序访问右子树
}

void PreOrderLoop(BiTNode *root) {
  std::stack<BiTNode *> s;
  BiTNode *cur, *top;
  cur = root;
  while (cur != NULL || !s.empty())
  {
    while (cur != NULL)
    {
      cout << cur->value << " ";
      s.push(cur);
      cur = cur->lchild;
    }

    top = s.top();
    s.pop();
    cur = top->rchild;
  }
}

void InOrder(const BiTNode *root) {
  if (root == NULL) {
    cout << "# ";
    return;
  }
  InOrder(root->lchild);            //前序访问左子树
  cout << root->value << " ";       //输出根节点的值
  InOrder(root->rchild);            //前序访问右子树
}

void InOrderLoop(BiTNode *root) {
  std::stack<BiTNode *> s;
  BiTNode *cur;
  cur = root;
  while (cur != NULL || !s.empty())
  {
    while (cur != NULL) {
      s.push(cur);
      cur = cur->lchild;
    }

    cur = s.top();
    s.pop();
    cout << cur->value << " ";
    cur = cur->rchild;
  }
}

void PostOrder(const BiTNode *root) {
  if (root == NULL) {
    cout << "# ";
    return;
  }
  PostOrder(root->lchild);            //前序访问左子树
  PostOrder(root->rchild);            //前序访问右子树
  cout << root->value << " ";         //输出根节点的值
}

void PostOrderLoop(BiTNode *root) {
  std::stack<BiTNode *> s;
  BiTNode *cur, *top, *last = NULL;
  cur = root;
  while (cur != NULL || !s.empty())
  {
    while (cur != NULL) {
      s.push(cur);
      cur = cur->lchild;
    }

    top = s.top();

    if (top->rchild == NULL || top->rchild == last) {
      s.pop();
      cout << top->value << " ";
      last = top;
    }
    else {
      cur = top->rchild;
    }
  }
}

int main() {
  vector<int> src_nodes({ 6,
                          1,                  12,
                          0,        3,        10,     13,
                          '#', '#', '#', '#', 4,  14, 20, 16,
                          2,  5, 11, 15, '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' });
  vector<int> src_nodes2({ 2,
                           3,      4,
                           5, 6, '#', '#',
                           7, 8, '#', 9, '#', '#', '#', '#' });
  binaryTree tree1, tree2;
  tree1.generateFixedBinaryTree(src_nodes);
  tree1.binaryTreePrint();
//  tree2.generateFixedBinaryTree(src_nodes2);
//  tree2.binaryTreePrint();

//  int depth = LevelOrder(tree1.src_root);
//  cout << "\ntree depth: " << depth << endl;

//  PreOrder(tree1.src_root);
//  PreOrderLoop(tree1.src_root);
//  InOrder(tree1.src_root);
//  InOrderLoop(tree1.src_root);
//  PostOrder(tree1.src_root);
  PostOrderLoop(tree1.src_root);

  return 0;
}
