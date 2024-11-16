#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> arr;

int binary_search(int left, int right, int target, vector<int> & answer) {

  while(left  < right) {
    int mid = (left + right) / 2;
    if(answer[mid] < target) left = mid + 1;
    else right = mid;
  }

  return right;
}

int main() {

  cin >> N;

  arr.resize(N);
  for(int idx=0; idx<N; idx++) {
    cin >> arr[idx];
  }

  vector<int> answer;
  answer.push_back(-1);
  for(int current=0; current<arr.size(); current++) {
    if(answer.back() <= arr[current]) {
      answer.push_back(arr[current]);
    }
    else {
      int idx = binary_search(0, answer.size()-1, arr[current], answer);
      answer[idx] = arr[current];
    }
  }

  cout << N - answer.size() + 1 << endl;

}