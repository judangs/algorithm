#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, m, c;

int dp[101][10001] = {0, };
vector<pair<int, int>> app;

int solve() {

    for(int idx=1; idx<=N; idx++) {
        for(int cost=0; cost <= 10000; cost++) {
            if(app[idx].second <= cost) {
                dp[idx][cost] = max(dp[idx - 1][cost - app[idx].second] + app[idx].first, dp[idx - 1][cost]);
            }
            else
                dp[idx][cost] = dp[idx - 1][cost];
        }
    }

    for(int cost=0; cost <= 10000; cost++) {
        if(dp[N][cost] >= M)
            return cost;
    }
}

int main() {
    cin >> N >> M;

    app.resize(N + 1, {0, 0});

    for(int i=1; i<=N; i++) {
        cin >> m;
        app[i].first = m;
    }

    for(int i=1; i<=N; i++) {
        cin >> c;
        app[i].second = c;
    }

    cout << solve();
}