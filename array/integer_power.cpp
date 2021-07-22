#include <bits/stdc++.h>

using namespace std;

/*
 * 输入一个不超过18位的正整数，判断是否可以通过改变各位数字的排列
 * 顺序（前面是0就删除），是新得到的整数是2的整数次幂。
 * 要求在PC上1秒之内能判断出来。
 */
bool IsTwoIntegerPower(const string& num_bits) {
  int zero_count = 0;
  for(int i = 0; i < num_bits.size(); ++i) {
    if(num_bits[i] == '0') zero_count++;
  }

  int min_bit_count = num_bits.size() - zero_count;
  int max_bit_count = num_bits.size();
  int current_bit_count = min_bit_count;
  unsigned long current_value_min = pow(10, current_bit_count-1);
  unsigned long current_value_max = pow(10, current_bit_count) - 1;
  vector<vector<vector<int> > >bit_indices(zero_count+1);
  vector<vector<int> > multi_num_indices;
  for(int i = 0; i <= 63; ++i) {
    unsigned long val = pow(2, i);
    if(val < current_value_min) continue;

    if(val >= current_value_min && val <= current_value_max) {
      vector<int> num_index(10, 0);
      int bit_count = 1;
      while(bit_count <= current_bit_count) {
        int div = 10;
        int n = val % div;
        num_index[n]++;
        val = (val - n) / 10;
        bit_count++;
      }
      multi_num_indices.push_back(num_index);
    } else {
      bit_indices[current_bit_count-min_bit_count] = multi_num_indices;
      multi_num_indices.clear();
      current_bit_count++;
      if(current_bit_count > max_bit_count) break;

      current_value_min = pow(10, current_bit_count-1);
      current_value_max = pow(10, current_bit_count) - 1;
      if(val >= current_value_min && val <= current_value_max) {
        vector<int> num_index(10, 0);
        int bit_count = 1;
        while(bit_count <= current_bit_count) {
          long n = val % 10;
          num_index[n]++;
          val = (val - n) / 10;
          bit_count++;
        }
        multi_num_indices.push_back(num_index);
      }
    }
  }
  if(bit_indices[zero_count].empty()) bit_indices[zero_count] = multi_num_indices;

  for(int i = 0; i <= zero_count; ++i) {
    vector<vector<int> > multi_num_indices = bit_indices[i];
    for(int j = 0; j < multi_num_indices.size(); ++j) {
      vector<int> num_index = multi_num_indices[j];
      if(num_index.empty()) continue;
      int ignore_zero = zero_count - i;
      for(int k = 0; k < num_bits.size(); ++k) {
        if(ignore_zero > 0 && num_bits[k] == '0') {
          ignore_zero--;
          continue;
        }
        num_index[num_bits[k]-'0']--;
      }
      int sum = 0;
      for(int k = 0; k < 10; ++k) {
        sum += abs(num_index[k]);
      }
      if(sum == 0) return true;
    }
  }

  return false;
}

bool IsTwoIntegerPowerV2(const string& num_bits) {
  int zero_count = 0;
  for(int i = 0; i < num_bits.size(); ++i) {
    if(num_bits[i] == '0') zero_count++;
  }

  int min_bit_count = num_bits.size() - zero_count;
  int max_bit_count = num_bits.size();
  int current_bit_count = min_bit_count;
  unsigned long current_value_min = pow(10, current_bit_count-1);
  unsigned long current_value_max = pow(10, current_bit_count) - 1;
  vector<vector<vector<int> > >bit_indices(zero_count+1);
  vector<vector<int> > multi_num_indices;
  for(int i = 0; i <= 63; ++i) {
    unsigned long val = pow(2, i);
    if (val < current_value_min) continue;

    if(val > current_value_max) {
      current_bit_count++;
      if (current_bit_count > max_bit_count) break;
      current_value_min = pow(10, current_bit_count - 1);
      current_value_max = pow(10, current_bit_count) - 1;
    }
    vector<int> num_index(10, 0);
    int bit_count = 1;
    while (bit_count <= current_bit_count) {
      long n = val % 10;
      num_index[n]++;
      val = (val - n) / 10;
      bit_count++;
    }

    int ignore_zero = max_bit_count - current_bit_count;
    for(int j = 0; j < num_bits.size(); ++j) {
      if(ignore_zero > 0 && num_bits[j] == '0') {
        ignore_zero--;
        continue;
      }
      num_index[num_bits[j] - '0']--;
    }
    int sum = 0;
    for(int j = 0; j < 10; ++j) {
      sum += abs(num_index[j]);
    }
    if(sum == 0) return true;
  }

  return false;
}

int main() {
  string num_bits;
  getline(cin, num_bits);
  assert(num_bits.size() <= 19);

  bool is_integer_power = IsTwoIntegerPowerV2(num_bits);
  if(is_integer_power) cout << "YES" << endl;
  else cout << "NO" << endl;

  unsigned long d = pow(2, 64);
  unsigned long a = (unsigned long)pow(2, 64) - (unsigned long)1;
  unsigned long b = (unsigned long)pow(2, 64) - 1;
  unsigned long c = pow(2, 64) - 1;
  cout << d << endl;
  cout << a << endl;
  cout << b << endl;
  cout << c << endl;
  cout << a + 1 << endl;
  cout << 0 - 1 << endl;
  cout << (unsigned long)0 - 1 << endl;
  cout << (unsigned int)0 - 1 << endl;

  return 0;
}
