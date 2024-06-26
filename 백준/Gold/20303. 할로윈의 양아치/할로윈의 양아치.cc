#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

int N, M, K;
int a, b;
vector<int> candy;
vector<int> parent;
vector<pair<int, int>> info;

int find(int start) {
    if(start == parent[start])
        return start;
    return find(parent[start]);
}

int main() {
    cin >> N >> M >> K;

    info.resize(N + 1, {0, 0});
    candy.resize(N + 1);
    parent.resize(N + 1);
    for(int i=1; i<=N; i++) parent[i] = i;

    for(int i=1; i<=N; i++) {
        cin >> candy[i];
    }

    for(int i=0; i<M; i++) {
        cin >> a >> b;
        a = find(a);
        b = find(b);
        if(a != b) {
            if(a < b) parent[b] = a;
            else parent[a] = b;
        }
    }

    for(int i=1; i<=N; i++) {
        int p = find(i);
        info[p].first++;
        info[p].second += candy[i];
    }

    vector<vector<int>> dp(N + 1, vector<int>(3001, 0));
    for(int idx=1; idx<dp.size(); idx++) {
        for(int member=0; member<=3000; member++) {
            if( info[idx].first <= member) {
                dp[idx][member] = max(dp[idx - 1][member], dp[idx - 1][member - info[idx].first] + info[idx].second);
            }
            else
                dp[idx][member] = dp[idx - 1][member];
        }
    }

    int answer = 0;
    for(int i=0; i<K; i++) {
        answer = max(answer, dp[N][i]);
    }

    cout << answer;
}

