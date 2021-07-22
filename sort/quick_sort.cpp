#include <bits/stdc++.h>

using namespace std;

void QuickSort(vector<int>& v, int low, int high) {
  if (low >= high) return;
  int first = low;
  int last = high;
  int key = v[first];

  while (first < last) {
    while (first < last && v[last] >= key) last--;
    if (first < last) v[first++] = v[last];

    while (first < last && v[first] <= key) first++;
    if (first < last) v[last--] = v[first];
  }
  v[first] = key;
  QuickSort(v, low, first-1);
  QuickSort(v, first+1, high);
}

int main() {
  vector<int> array = { 5, 7, 1, 3, 2, 7 };
  QuickSort(array, 0, array.size()-1);
  for (int e : array) {
    cout << e << " ";
  }
  cout << endl;

  return 0;
}
