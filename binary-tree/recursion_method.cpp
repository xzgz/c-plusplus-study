#include <iostream>
#include <vector>

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

struct Info1 {
    bool is_balanced;
    int height;
    Info1(bool b, int h) {
        is_balanced = b;
        height = h;
    }
};

Info1 Process1(Node *head) {
    if (head == nullptr) {
        return Info1(true, 0);
    }
    Info1 left_info = Process1(head->left);
    Info1 right_info = Process1(head->right);

    bool is_balanced = left_info.is_balanced && right_info.is_balanced && abs(left_info.height - right_info.height) <= 1;
    int height = max(left_info.height, right_info.height) + 1;
    return Info1(is_balanced, height);
}

bool IsBalanced(Node *head) {
    return Process1(head).is_balanced;
}


struct Info2 {
    int max_distance;
    int height;
    Info2(int md, int h) {
        max_distance = md;
        height = h;
    }
};

Info2 Process2(Node *head) {
    if (head == nullptr) {
        return Info2(0, 0);
    }
    Info2 left_info = Process2(head->left);
    Info2 right_info = Process2(head->right);

    int max_distance = max(max(left_info.max_distance, right_info.max_distance), left_info.height + right_info.height + 1);
    int height = max(left_info.height, right_info.height) + 1;
    return Info2(max_distance, height);
}

int MaxDistance(Node *head) {
    return Process2(head).max_distance;
}


struct Info3 {
    bool is_all_bst;
    int max_sub_bst_size;
    int min_value;
    int max_value;
    Info3(bool is, int max_sub, int min_val, int max_val) {
        is_all_bst = is;
        max_sub_bst_size = max_sub;
        min_value = min_val;
        max_value = max_val;
    }
};

Info3 *Process3(Node *head) {
    if (head == nullptr) {
        return nullptr;
    }
    Info3 *left_info = Process3(head->left);
    Info3 *right_info = Process3(head->right);
    if (head->value == 5) {
        cout << endl;
    }

    int min_val = head->value;
    int max_val = head->value;
    int max_sub_bst_size = 0;
    if (left_info != nullptr) {
        min_val = min(left_info->min_value, min_val);
        max_val = max(left_info->max_value, max_val);
        max_sub_bst_size = max(left_info->max_sub_bst_size, max_sub_bst_size);
    }
    if (right_info != nullptr) {
        min_val = min(right_info->min_value, min_val);
        max_val = max(right_info->max_value, max_val);
        max_sub_bst_size = max(right_info->max_sub_bst_size, max_sub_bst_size);
    }
    bool is_all_bst = false;
    if ((left_info == nullptr ? true : left_info->is_all_bst && left_info->max_value < head->value) &&
        (right_info == nullptr ? true : right_info->is_all_bst && head->value < right_info->min_value)) {
        is_all_bst = true;
        max_sub_bst_size = (left_info == nullptr ? 0 : left_info->max_sub_bst_size)
                + (right_info == nullptr ? 0 : right_info->max_sub_bst_size) + 1;
    }
//    cout << "val: " << head->value << " max_sub_bst_size: " << max_sub_bst_size << endl;
    return new Info3(is_all_bst, max_sub_bst_size, min_val, max_val);
}

int MaxSubBstSize(Node *head) {
    Info3 *info3_ptr = Process3(head);
    if (info3_ptr == nullptr) {
        return 0;
    } else {
        return info3_ptr->max_sub_bst_size;
    }
}


/*
 * 派对的最大快乐值
 * 某个公司现在要办party，你可以决定哪些员工来，哪些员工不来，规则：
 * 1、如果某个员工来了，那么这个员工的所有直接下级都不能来；
 * 2、派对的整体快乐值是所有到场员工快乐值的累加；
 * 3、你的目标是让派对的整体快乐值达到最大。
 * 给定一棵多叉树的头结点boss，请返回派对的最大快乐值。
 */
struct Employee {
    int happy;
    vector<Employee> nexts;
    Employee(int h) {
        happy = h;
    }
};

struct Info4 {
    int yes;
    int no;
    Info4(int y, int n) {
        yes = y;
        no = n;
    }
};

Info4 Process4(Employee x) {
    if (x.nexts.empty()) {
        return Info4(x.happy, 0);
    }

    int yes = x.happy;
    int no = 0;
    for (Employee next : x.nexts) {
        Info4 next_info = Process4(next);
        yes += next_info.no;
        no += max(next_info.yes, next_info.no);
    }
    return Info4(yes, no);
}

int MaxHappy(Employee *boss) {
    if (boss == nullptr) {
        return 0;
    } else {
        Info4 info_all = Process4(*boss);
        return max(info_all.yes, info_all.no);
    }
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
    n0->right->right->right->right = new Node(11);

    return n0;
}

Node *ConstructBinarySearchTree() {
    Node *n0 = new Node(11);
    Node *n1 = new Node(3);
    Node *n2 = new Node(12);
    Node *n3 = new Node(1);
    Node *n4 = new Node(5);
    Node *n5 = new Node(11);
    Node *n6 = new Node(14);
    Node *n7 = new Node(2);
    Node *n8 = new Node(4);
    Node *n9 = new Node(6);
    Node *n10 = new Node(13);
    Node *n11 = new Node(15);
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
    n0->right->right->right->right = new Node(16);

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
    PrintTreePerfect(head);
    Node *bst = ConstructBinarySearchTree();
    PrintTreePerfect(bst);

    bool is_balanced = IsBalanced(head);
    int max_distance = MaxDistance(head);
    int max_sub_bst_size = MaxSubBstSize(bst);
    cout << "is_balanced: " << is_balanced << endl;
    cout << "max_distance: " << max_distance << endl;
    cout << "max_sub_bst_size: " << max_sub_bst_size << endl;

    return 0;
}
