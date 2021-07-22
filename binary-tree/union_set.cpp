#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template <typename T>
struct Node {
    T value;
    Node() {}
    Node(T v) {
        value = v;
    }
    friend bool operator==(const Node& a, const Node& b) {
        return a.value == b.value;
    }
    bool operator!=(const Node& b) {
        return this->value != b.value;
    }
};

struct User {
    string a;
    string b;
    string c;
    User() {};
    User(const string& s0, const string& s1, const string& s2) {
        a = s0;
        b = s1;
        c = s2;
    }
    friend bool operator!=(const User& a, const User& b) {
        return a.a != b.a || a.b != b.b || a.c != b.c;
    }
    friend bool operator==(const User& a, const User& b) {
        return !(a != b);
    }
};

namespace std {
    template <>
    class hash<User> {
    public:
        const size_t operator()(const User& u) const {
            size_t h = hash<string>()(u.a + u.b + u.c);
            return h;
        }
    };
    template <>
    class hash<Node<User> > {
    public:
        size_t operator()(const Node<User>& node) const {
            size_t h = hash<string>()(node.value.a + node.value.b + node.value.c);
            return h;
        }
    };
}


template <typename T>
class UnionSet {
public:
    UnionSet(vector<T> values) {
        for (T val : values) {
            Node<T> node = Node<T>(val);
            nodes[val] = node;
            parents[node] = node;
            map_size[node] = 1;
        }
    }
    Node<T> FindFather(Node<T>& node) {
        stack<Node<T> > path;
        while (node != parents[node]) {
            path.push(node);
            node = parents[node];
        }
        while (!path.empty()) {
            parents[path.top()] = node;
            path.pop();
        }
        return node;
    }
    bool IsSameSet(T a, T b) {
        if (nodes.count(a) == 0 || nodes.count(b) == 0) {
            return false;
        } else {
            return FindFather(nodes[a]) == FindFather(nodes[b]);
        }
    }
    void Union(T a, T b) {
        if (nodes.count(a) == 0 || nodes.count(b) == 0) {
            return;
        }
        Node<T> a_head = FindFather(nodes[a]);
        Node<T> b_head = FindFather(nodes[b]);
        if (a_head != b_head) {
            int a_set_size = map_size[a_head];
            int b_set_size = map_size[b_head];
            Node<T> big = a_set_size > b_set_size ? a_head : b_head;
            Node<T> small = big == a_head ? b_head : a_head;
            parents[small] = big;
            map_size[big] = a_set_size + b_set_size;
            map_size.erase(small);
        }
    }
    int GetSetSize() {
        return map_size.size();
    }

private:
    unordered_map<T, Node<T> > nodes;
    unordered_map<Node<T>, Node<T> > parents;
    unordered_map<Node<T>, int> map_size;
};

int MergeUsers(vector<User> users) {
    UnionSet<User> union_user = UnionSet<User>(users);
    unordered_map<string, User> map_a, map_b, map_c;
    for (User user : users) {
        if (map_a.count(user.a) != 0) {
            union_user.Union(user, map_a[user.a]);
        } else {
            map_a[user.a] = user;
        }

        if (map_b.count(user.b) != 0) {
            union_user.Union(user, map_b[user.b]);
        } else {
            map_b[user.b] = user;
        }

        if (map_c.count(user.c) != 0) {
            union_user.Union(user, map_c[user.c]);
        } else {
            map_c[user.c] = user;
        }
    }
    return union_user.GetSetSize();
}

void TestMergeUsers() {
    cout << "TestMergeUsers():" << endl;
    vector<User> users(5);
    User u1 = User("a1", "b1", "c1");
    User u2 = User("a2", "b2", "c2");
    User u3 = User("a1", "b3", "c3");
    User u4 = User("a4", "b1", "c4");
    User u5 = User("a2", "b5", "c5");
    users[0] = u1;
    users[1] = u2;
    users[2] = u3;
    users[3] = u4;
    users[4] = u5;
    int user_count = MergeUsers(users);
    cout << "user_count: " << user_count << endl;
}

int main() {
    TestMergeUsers();

    return 0;
}
