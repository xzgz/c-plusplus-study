//#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void String2IntArray(vector<int>& array, string& str) {
  int str_len = str.size();
  int s, e;
  for (int i = 0; i < str_len; ++i) {
	if ('0' <= str[i] && str[i] <= '9') {
	  s = i;
	  e = i;
	  int j = s + 1;
	  for (; j < str_len; ++j) {
		if (str[j] < '0' || str[j] > '9') {
		  e = j;
		  break;
		}
	  }
	  if (j == str_len) e = j;
	  if (s != e) array.push_back(stoi(str.substr(s, e-s)));
	  i = e;
	}
  }
}

void String2IntArray2(vector<int>& array, string str) {
  long order;
  while (!str.empty()) {
	string::iterator loc = find(str.begin(), str.end(), ' ');
	order = distance(str.begin(), loc);
	array.push_back(stoi(str.substr(0, order)));
	str.erase(0, 1+order);
  }
}
