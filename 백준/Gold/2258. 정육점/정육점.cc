#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<long long, long long> meat;

int N, M;
long long  w, c;

vector<meat> prefix;
vector<int> weight;

bool compare(meat lhs, meat rhs) {
    if(lhs.second == rhs.second) {
        return lhs.first > rhs.first;
    }
    return lhs.second < rhs.second;
}

int main() {
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        cin >> w >> c;
        prefix.push_back({w, c});
    }
    
    if(prefix.front().first >= M) {
        cout << prefix.front().second;
        return 0;
    }
    
    weight.resize(prefix.size(), 1);
    
    sort(prefix.begin(), prefix.end(), compare);
    
    long long answer = 1e18;
    for(int current=0; current<prefix.size() - 1; current++) {
        int next = current + 1;
        if(prefix[current].second == prefix[next].second) {
            weight[next] = weight[current] + 1;
        }
        
        prefix[next].first += prefix[current].first;
        if(prefix[next].first >= M) {
            long long calc = prefix[next].second * weight[next];
            answer = min(answer, calc);
        }
    }
    
    cout << (answer != 1e18 ? answer : -1);
    
}