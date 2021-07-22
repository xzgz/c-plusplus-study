#include <bits/stdc++.h>

using namespace std;

/*
题目描述：输入2行数字，分别表示数组A和B，每一行数字间用空格隔开。A不是严格单调递增的，但若用一个合适的值将A中
的某一个元素替换，A就变成了严格单调递增的。现在需要从B中寻找满足改要求的最大数字，若能找到就打印替换之后的A，否则打印NO。
*/
int main() {
  vector<int> A;
  vector<int> B;
  string line_data;
  long order;

  getline(cin, line_data);
  while(!line_data.empty()) {
    string::iterator loc = find(line_data.begin(), line_data.end(), ' ');
    order = distance(line_data.begin(), loc);
    A.push_back(stoi(line_data.substr(0, order)));
    line_data.erase(0, 1+order);
  }
  getline(cin, line_data);
  while(!line_data.empty()) {
    string::iterator loc = find(line_data.begin(), line_data.end(), ' ');
    order = distance(line_data.begin(), loc);
    B.push_back(stoi(line_data.substr(0, order)));
    line_data.erase(0, 1+order);
  }

  if(B.empty()) {
    cout << "NO";
    return 0;
  }

  int len_a = A.size();
  int len_b = B.size();
  assert(len_a >= 2);
  if(len_a == 2)  // only 2 number case
  {
    assert(A[0] > A[1]);
    int max_l = -INT_MAX, max_r = -INT_MAX;
    for(int i = 0; i < B.size(); ++i)
    {
      if(B[i] < A[1] && B[i] > max_l) max_l = B[i];
      if(B[i] > A[0] && B[i] > max_r) max_r = B[i];
    }
    if(max_l == -INT_MAX && max_r == -INT_MAX)
    {
      cout << "NO";
      return 0;
    }
    else
    {
      (max_l > max_r) ? (A[0] = max_l) : (A[1] = max_r);
    }
  }     // end of only 2 number case
  else  // number count >= 3 case
  {
    int max_replace = -INT_MAX;
    int max_l = -INT_MAX, max_r = -INT_MAX;
    for(int i = 0; i <= len_a-3; ++i)
    {
      if(A[i] > A[i+1])  // idx > idx+1, this case will have 2 subcases
      {
        if(A[i] > A[i+2])  // subcase 1, idx > idx+2, idx will probably be replaced
        {
          if(i > 0)
          {
            for(int j = 0; j < len_b; ++j)
              if(A[i-1] < B[j] && B[j] < A[i+1] && B[j] > max_replace) max_replace = B[j];
          }
          else
          {
            for(int j = 0; j < len_b; ++j)
              if(B[j] < A[i+1] && B[j] > max_replace) max_replace = B[j];
          }
          if(max_replace == -INT_MAX)
          {
            cout << "NO";
            return 0;
          }
          else
          {
            A[i] = max_replace;  // idx is replaced
          }
        }  // end of subcase 1
        else  // subcase 2, idx < idx+2, idx and idx+1 would probably be replaced
        {
          for(int j = 0; j < len_b; ++j)
          {
            if(i > 0)
            {
              if(A[i-1] < B[j] && B[j] < A[i+1] && B[j] > max_l) max_l = B[j];
            }
            else
            {
              if(B[j] < A[i+1] && B[j] > max_l) max_l = B[j];
            }
            if(A[i] < B[j] && B[j] < A[i+2] && B[j] > max_r) max_r = B[j];
          }
          if(max_l == -INT_MAX && max_r == -INT_MAX)
          {
            cout << "NO";
            return 0;
          }
          else
          {
            (max_l > max_r) ? (A[i] = max_l) : (A[i+1] = max_r);
          }
        }  // end of subcase 2
      }  // end of case idx > idx+1
    }
    if(max_replace == -INT_MAX && max_l == -INT_MAX && max_r == -INT_MAX)  // the last number should be replaced
    {
      assert(A[len_a-2] > A[len_a-1]);
      for(int j = 0; j < len_b; ++j)
      {
        if(B[j] > A[len_a-2] && B[j] > max_r) max_r = B[j];
        if(B[j] > A[len_a-3] && B[j] < A[len_a-1] && B[j] > max_l) max_l = B[j];
      }
      if(max_l == -INT_MAX && max_r == -INT_MAX)
      {
        cout << "NO";
        return 0;
      }
      else
      {
        (max_l > max_r) ? (A[len_a-2] = max_l) : (A[len_a-1] = max_r);
      }
    }
  }  // end of number count >= 3 case

  for(int i = 0; i < len_a; ++i) cout << A[i] << ' ';
  return 0;
}
