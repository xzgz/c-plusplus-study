#include <bits/stdc++.h>

using namespace std;

bool DFSJudge(const vector<string>& str_arr, const string& visited = string()) {
  static int status = 0;
  if(status == 1) {
    return false;
  } else if(status == 2) {
    return true;
  }
  if(str_arr.empty() && !visited.empty() && visited[0]==visited[1]) {
    status = 2;
    return true;
  } else if(str_arr.empty()) {
    return false;
  }

  for(int i = 0; i < str_arr.size(); ++i) {
    if(str_arr[i].size() <= 1) {
      status = 1;
      return false;
    }
    if(status) continue;

    vector<string> rem_str;
    string vt_str;
    vt_str.resize(2);
    if(visited.empty() || str_arr[i][0] == visited[1]) {
      rem_str.resize(str_arr.size()-1);
      int offset = 0;
      for(int j = 0; j < str_arr.size(); ++j) {
        if(j == i) {
          offset += 1;
          continue;
        }
        rem_str[j-offset] = str_arr[j];
      }

      if(visited.empty()) {
        char vt_char_arr[] = { str_arr[i][0], str_arr[i][str_arr[i].size()-1] };
        vt_str = vt_char_arr;
        DFSJudge(rem_str, vt_str);
      }
      if (str_arr[i][0] == visited[1]) {
        vt_str[0] = visited[0];
        vt_str[1] = str_arr[i][str_arr[i].size() - 1];
        DFSJudge(rem_str, vt_str);
      }
    }
  }

  if(status == 1 || status == 0) {
    return false;
  } else if(status == 2) {
    return true;
  }
}

bool MapJudge(const vector<string>& str_arr) {
  map<char, char> circle_node;
  char first_char, end_char;
  for(int i = 0; i < str_arr.size(); ++i) {
    string str = str_arr[i];
    first_char = str[0];
    end_char = str[str.size()-1];
    circle_node[first_char] = end_char;
  }

  string first_str = str_arr[0];
  first_char = first_str[0];
  char start_char = circle_node[first_str[first_str.size()-1]];
  while(start_char) {
    if(start_char == first_char) {
      return true;
    }
    start_char = circle_node[start_char];
  }
  return false;
}

int main() {
  vector<string> str_arr;
  string line_data;
  long order;
  getline(cin, line_data);
  while(!line_data.empty()) {
    string::iterator loc = find(line_data.begin(), line_data.end(), ' ');
    cout << int(*loc) << endl;
    order = distance(line_data.begin(), loc);
    str_arr.push_back(line_data.substr(0, order));
    line_data.erase(0, 1+order);
  }

  bool exist_circle = DFSJudge(str_arr);
//  bool exist_circle = MapJudge(str_array);
  if(exist_circle) {
    cout << "True\n";
  } else {
    cout << "False\n";
  }

  char ch_arr[] = { 'q', 'w', 's', 'o', 0, 0, 0 };
  string str = ch_arr;
  cout << str << endl << str.size() << endl;
  cout << str << endl << str.size() << " " << str.capacity() << endl;
  str.reserve(34);
  cout << str << endl << str.size() << " " << str.capacity() << endl;
  str.resize(2);
  cout << str << endl << str.size() << " " << str.capacity() << endl;
  str.resize(5);
  cout << str << endl << str.size() << " " << str.capacity() << endl;

  string str_pt = "1234";
  string::iterator pb = str_pt.begin();
  string::iterator pe = str_pt.end();
  cout << *pb << endl;
  cout << *pe << endl;
  cout << *(pe-1) << endl;
  cout << str_pt << ' ' << str_pt.size() << endl;
  *pb = 'a';
  *pe = 'p';
  pe = str_pt.end();
  cout << *pe << endl;
  cout << str_pt << ' ' << str_pt.size() << endl;

  return 0;
}
