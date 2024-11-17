#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int, int> pii;

int N;
vector<pii> other;

int binary_search(vector<int> & lis, int left, int right, int target) {

  while(left + 1 < right) {
    int mid = (left + right) / 2;
    if(lis[mid] < target) left = mid;
    else right = mid;
  }

  return right;
}

int main() {

  cin >> N;
  vector<int> start(N);
  for(int idx=0; idx<N; idx++) {
    cin >> start[idx]; // idx button number
  }

  map<int, int> lines;

  int num;
  for(int idx=1; idx<=N; idx++) {
    cin >> num;
    lines[num] = idx;
  }

  for(int idx=0; idx<N; idx++) {
    int dest = lines[start[idx]];
    other.push_back({start[idx], dest}); // first: button number, second : dest pos
  }

  vector<int> lis;
  vector<int> index(N);
  lis.push_back(-1);
  for(int idx=0; idx<other.size(); idx++) {
    if(lis.back() < other[idx].second) {
      lis.push_back(other[idx].second);
      index[idx] = lis.size() - 1;
    }
    else {
      int insert = binary_search(lis, 0, lis.size(), other[idx].second);
      lis[insert] = other[idx].second;
      index[idx] = insert;
    }
  }
  
  int last = lis.size() - 1;
  vector<int> answer;
  for(int ptr=index.size()-1; ptr>=0; ptr--) {
    if(index[ptr] == last) {
      answer.push_back(other[ptr].first);
      last--;
    }
  }

  sort(answer.begin(), answer.end());
  
  cout << answer.size() << "\n";
  for(int ans: answer) {
    cout << ans << " ";
  }
}