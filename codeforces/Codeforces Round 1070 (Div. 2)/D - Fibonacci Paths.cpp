#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define MOD 998244353

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

int t;
struct Edge {
    ll sum;
    int s;
    int e;
};

int main() {

    fastio;
    cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        vector<ll> vertex(n);
        vector<Edge> edge(m);
        vector<unordered_map<ll, ll>> dp(n);
        for(auto & av: vertex) cin >> av;
        for(int i = 0; i < m; i++) {
            int s, e; cin >> s >> e;
            --s; --e;
            edge[i] = { vertex[s] + vertex[e], s, e };
        }
        
        sort(edge.begin(), edge.end(), [](const Edge & l, const Edge & r) {
            return l.sum > r.sum;
        });

        ll ans = 0ll;
        for(auto & [sum, s, e]: edge) {
            ll cur = (1 + dp[e][sum]) % MOD;
            dp[s][vertex[e]] = (dp[s][vertex[e]] + cur)  % MOD;
            ans = (ans + cur) % MOD;
            
        }
        
        cout << ans << "\n";
        
    }

}
