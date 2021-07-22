#include <bits/stdc++.h>

using namespace std;

/*
 * refer to: https://www.cnblogs.com/alantu2018/p/8471854.html
 * 从一个二叉搜索树中删除一个指定值的节点，要求删除该节点之后仍然是一个二叉搜索树，
 * 返回该树的根节点，并且要求标记原二叉树中是否存在这样一个指定值的节点。
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int val, TreeNode *left = NULL, TreeNode *right = NULL)
          : val(val), left(left), right(right) {}
};

TreeNode *FindMin(TreeNode *root) {
  if (root != NULL)
    while (root->left != NULL) root = root->left;

  return root;
}

TreeNode *SearchValue(TreeNode *root, int target, int& is_deleted) {
  if (root == NULL) return root;
  if (target < root->val) root->left = SearchValue(root->left, target, is_deleted);
  else if (target > root->val) root->right = SearchValue(root->right, target, is_deleted);
  else {
    TreeNode *temp;
    is_deleted = 1;
    if (root->left && root->right) {
      temp = FindMin(root->right);
      root->val = temp->val;
      root->right = SearchValue(root->right, root->val, is_deleted);
    } else {
      temp = root;
      if (root->left == NULL) root = root->right;
      else if (root->right == NULL) root = root->left;
      delete temp;
    }
  }
  if (is_deleted != 1) is_deleted = 0;

  return root;
}

int main() {
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(4);
  root->right->left = new TreeNode(3);
  root->right->right = new TreeNode(5);
  root->right->right->right = new TreeNode(6);
  int is_del = -1;
  SearchValue(root, 9, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, 6, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, 8, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, 5, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, 7, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, 4, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, 3, is_del);
  cout << is_del << endl;
  is_del = -1;
  root = SearchValue(root, 2, is_del);
  cout << is_del << endl;
  is_del = -1;
  root = SearchValue(root, 1, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, 0, is_del);
  cout << is_del << endl;
  is_del = -1;
  SearchValue(root, -1, is_del);
  cout << is_del << endl;

  return 0;
}
