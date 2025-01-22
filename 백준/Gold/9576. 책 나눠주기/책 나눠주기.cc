#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, M, a, b;
vector<pair<int, int>> arr;

bool compare(pair<int, int> a, pair<int, int> b) {
    if(a.second == b.second) {
        return a.first < b.first;
    }
    return a.second < b.second;
}

int main() {
    
    cin >> T;
    while(T--) {
        cin >> N >> M;
        for(int i=0; i<M; i++) {
            cin >> a >> b;
            arr.push_back({a, b});
        }
    
        sort(arr.begin(), arr.end(), compare);
        int current = arr.front().first;
        
        vector<bool> visit(N + 1, true);
        
        int answer = 0;
        for(int idx=0; idx<arr.size() && current <= N; idx++) {
            int start = arr[idx].first;
            int end = arr[idx].second;
            
            for(int book=start; book<=end; book++) {
                if(visit[book]) {
                    visit[book] = false;
                    answer++;
                    break;
                }
            }
        }
    
        arr.clear();
        cout << answer << "\n";
    }
}
