#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Node {
    int idx;
    ll a;
    bool operator>(const Node& o) const { return a > o.a; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<pair<ll,ll>> foods(N);
    for (auto &p: foods) cin >> p.first >> p.second;

    sort(foods.begin(), foods.end(), [](auto &l, auto &r){
        return l.second < r.second;
    });

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    for (int i = 0; i < N; i++) pq.push({i, foods[i].first});

    vector<char> used(N, 0);

    vector<ll> psum(N+1, 0);
    for (int i = 0; i < N; i++) psum[i+1] = psum[i] + foods[i].second;

    ll bestInside = (1LL<<62);

    for (int k = 1; k <= N; k++) {
        int t = k - 1;

        if (t > 0) {
            int idx = t - 1;
            used[idx] = 1;
            bestInside = min(bestInside, foods[idx].first - foods[idx].second);
        }

        while (!pq.empty() && used[pq.top().idx]) pq.pop();
        ll minAOutside = pq.top().a;

        ll ans = (1LL<<62);
        ans = min(ans, psum[t] + minAOutside);
        if (t > 0) {
            ans = min(ans, psum[k] + bestInside);
        }

        cout << ans << "\n";
    }

}
