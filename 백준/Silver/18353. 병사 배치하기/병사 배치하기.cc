#include <iostream>
#include <vector>

using namespace std;

int N;

int binary_search(vector<int> & soilder, int left, int right, int target) {
  while(left + 1 < right) {
    int mid = (left + right) / 2;
    if(soilder[mid] < target) right = mid;
    else left = mid;
  }

  return right;
}

int main() {

  cin >> N;

  vector<int> soilder(N);
  for(int idx=0; idx<N; idx++) {
    cin >> soilder[idx];
  }

  vector<int> lis;
  lis.push_back(INT32_MAX);
  for(int idx=0; idx<N; idx++) {
    if(lis.back() > soilder[idx]) {
      lis.push_back(soilder[idx]);
    }
    else {
      int insert = binary_search(lis, 0, lis.size(), soilder[idx]);
      lis[insert] = soilder[idx];
    }
  }

  cout << (N - lis.size() + 1);
}