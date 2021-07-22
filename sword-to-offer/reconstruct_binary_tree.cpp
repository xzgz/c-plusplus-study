#include <bits/stdc++.h>

using namespace std;

/*
refer to: https://blog.csdn.net/hh66__66hh/article/details/82939450
题目描述：
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例
如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，
则重建二叉树并返回。
 */
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

unordered_map<int, int> index_of_inorder;

/*
 * prel: the index in preorder array of value of current tree's first node in preorder (namely root node)
 * prer: the index in preorder array of value of current tree's last node in preorder
 * inl: the index in inorder array of value of the first node of left child of current tree in inorder
 */
TreeNode *reConstructBinaryTree(vector<int>& pre, int prel, int prer, int inl) {
  if (prel > prer) return NULL;
  TreeNode *root = new TreeNode(pre[prel]);
  int in_index = index_of_inorder[root->val];
  int left_tree_size = in_index - inl;
  root->left = reConstructBinaryTree(pre, prel+1, prel+left_tree_size, inl);
  root->right = reConstructBinaryTree(pre, prel+left_tree_size+1, prer, inl+left_tree_size+1);

  return root;
}

TreeNode *reConstructBinaryTree(vector<int>& pre, vector<int>& vin) {
  for (int i = 0; i < vin.size(); ++i) index_of_inorder[vin[i]] = i;
  return reConstructBinaryTree(pre, 0, pre.size()-1, 0);
}

/*
 * postr: the index in postorder array of value of current tree's last node in postorder (namely root node)
 * postl: the index in postorder array of value of current tree's first node in postorder
 * inl: the index in inorder array of value of the last node of right child of current tree in inorder
 */
TreeNode *ReconstructFromInPost(vector<int>& post, int postr, int postl, int inr) {
  if (postr < postl) return NULL;
  TreeNode *root = new TreeNode(post[postr]);
  int in_index = index_of_inorder[root->val];
  int right_tree_size = inr - in_index;
  root->right = ReconstructFromInPost(post, postr-1, postr-right_tree_size, inr);
  root->left = ReconstructFromInPost(post, postr-right_tree_size-1, postl, inr-right_tree_size-1);

  return root;
}

TreeNode *ReconstructFromInPost(vector<int>& vin, vector<int>& post) {
  for (int i = 0; i < vin.size(); ++i) index_of_inorder[vin[i]] = i;
  return ReconstructFromInPost(post, post.size()-1, 0, post.size()-1);
}

void SearchPreOrder(TreeNode *root) {
  if (root == NULL) return;
  cout << root->val << " ";
  SearchPreOrder(root->left);
  SearchPreOrder(root->right);
}

void SearchInOrder(TreeNode *root) {
  if (root == NULL) return;
  SearchInOrder(root->left);
  cout << root->val << " ";
  SearchInOrder(root->right);
}

void SearchPostOrder(TreeNode *root) {
  if (root == NULL) return;
  SearchPostOrder(root->left);
  SearchPostOrder(root->right);
  cout << root->val << " ";
}

int main() {
  vector<int> pre = { 4, 7, 9, 2, 1, 5, 6 };
  vector<int> vin = { 7, 9, 4, 1, 2, 6, 5 };
  vector<int> post = { 9, 7, 1, 6, 5, 2, 4 };

  TreeNode *root = reConstructBinaryTree(pre, vin);
  SearchPreOrder(root);
  cout << endl;
  SearchInOrder(root);
  cout << endl;
  SearchPostOrder(root);
  cout << endl;
  for (int n : post) cout << n << " ";
  cout << endl;

  root = ReconstructFromInPost(vin, post);
  SearchPreOrder(root);
  cout << endl;
  for (int n : pre) cout << n << " ";
  cout << endl;
  SearchInOrder(root);
  cout << endl;
  SearchPostOrder(root);
}
