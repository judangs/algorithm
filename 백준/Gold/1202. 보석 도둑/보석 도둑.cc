#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

int N, K, M, V, C;

vector<vector<int>> jewels;
vector<int> bags;

long long solve() {

    priority_queue<int, vector<int>, less<int>> pq;

    long long answer = 0;
    int current = 0;
    for(int bag: bags) {
        while(current < jewels.size() && jewels[current][0] <= bag) {
            pq.push(jewels[current][1]);
            current++;
        }

        if(pq.empty()) continue;
        answer += pq.top();
        pq.pop();
    }

    return answer;
}

int main() {
    cin >> N >> K;

    jewels.resize(N);
    bags.resize(K);
    
    for(int i=0; i<N; i++) {
        cin >> M >> V;
        jewels[i] = {M, V};
    }

    for(int i=0; i<K; i++) {
        cin >> C;
        bags[i] = C;
    }

    sort(jewels.begin(), jewels.end());
    sort(bags.begin(), bags.end());
    cout << solve();
}