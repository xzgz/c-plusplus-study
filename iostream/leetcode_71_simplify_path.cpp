#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void split(string s, char delim, vector<string>& nodes) {
    string temp;
    stringstream ss(s);
    while (getline(ss, temp, delim)) {
        nodes.push_back(temp);
    }
}

string simplifyPath(string path) {
    vector<string> st;
    vector<string> nodes;
    string result;
    split(path, '/', nodes);
    for (auto node : nodes) {
        if (node == "" || node == ".")  continue;
        if (node == ".." && !st.empty())  st.pop_back();
        else if (node != "..")  st.push_back(node);
    }
    for (auto it : st) result += "/" + it;
    return result.empty() ? "/" : result;
}

int main() {
    string path = "/usr////./local/../lib64/.../..//data///../../../../";
    string simplify_path = simplifyPath(path);
    cout << simplify_path << endl;

    return 0;
}
