#include <bits/stdc++.h>
#include "include/tree.h"

using namespace std;

// refer to: https://www.jianshu.com/p/a424af3540e0

int MaxDepthLevel(BiTNode *root) {
  if(root == NULL)
    return 0;

  int depth = 0;
  queue<BiTNode *> q;
  q.push(root);
  while(!q.empty())
  {
    ++depth;
    cout << "\ndepth " << depth << ": ";
    int level_num = q.size();
    for (int i = 0; i < level_num; ++i)
    {
      BiTNode *p = q.front();
      q.pop();
      cout << p->value << " ";

      if(p->lchild != NULL)
        q.push(p->lchild);
      if(p->rchild != NULL)
        q.push(p->rchild);
    }
  }

  return depth;
}

int MaxDepthPre(BiTNode *root) {
  BiTNode *p = root;
  BiTNode *r = nullptr;
  int max = 0;    // 树高
  stack<BiTNode*> s;
  while(p || !s.empty())
  {
    if(p != nullptr) {
      s.push(p);
      p = p->lchild;
    }
    else {
      p = s.top();
      if(p->rchild != nullptr && p->rchild != r)      // p有右孩子，且右孩子未进过栈
        p = p->rchild;
      else {
        if (s.size() > max) max = s.size();           // 更新最大高度
        r = p;                                        // 记录上一个弹出栈的节点
        s.pop();
        p = nullptr;
      }
    }
  }

  return max;
}

int MaxDepthRecursion(BiTNode *root) {
  return root == NULL ? 0 : max(MaxDepthRecursion(root->lchild), MaxDepthRecursion(root->rchild)) + 1;
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

  int depth;

  depth = MaxDepthLevel(tree1.src_root);
  cout << "\ntree depth: " << depth << endl;

  depth = MaxDepthRecursion(tree1.src_root);
  cout << "\ntree depth: " << depth << endl;

  depth = MaxDepthPre(tree1.src_root);
  cout << "\ntree depth: " << depth << endl;

  return 0;
}
