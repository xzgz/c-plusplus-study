#include "common_function.h"
#include <iostream>

using namespace std;

void Swap(char& a, char& b) {
    char temp = a;
    a = b;
    b = temp;
}

void Process(string str, int i, vector<string>& res) {
    if (i == str.length()) {
        res.push_back(str);
        return;
    }
    bool visited[26] = { 0 };
    for (int j = i; j < str.length(); ++j) {
        if (!visited[str[j] - 'a']) {
            visited[str[j] - 'a'] = true;
            Swap(str[i], str[j]);
            Process(str, i + 1, res);
            Swap(str[i], str[j]);
        }
    }
}

int main() {
    string str = "aaab";
    vector<string> res;
    Process(str, 0, res);
    for (const string& v : res) cout << v << endl;
    for (int i = 0; i <= str.length(); ++i) {
        cout << int(str[i]) << endl;
    }
}
