#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
int N;
vector<int> node;
vector<vector<int>> adj;
vector<vector<ll>> dp;

void dfs(int now, int parent) {
    
    dp[now][node[now]] = 1ll;

    for(auto child: adj[now]) {
        if(child != parent) {
            dfs(child, now);
            for(int i = 0; i < 10; i++)
                dp[now][i] = (dp[now][i] + dp[child][i]) % mod;
            for(int i = node[now]; i < 10; i++)
                dp[now][node[now]] = (dp[now][node[now]] + dp[child][i]) % mod;
        }
    }
}

int main() {

    cin >> N;
    node = vector<int>(N + 1);
    adj = vector<vector<int>>(N + 1);
    dp = vector<vector<ll>>(N + 1, vector<ll>(10));
    for(int i = 1; i <= N; i++) cin >> node[i];
    for(int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, 0);
    ll ans = 0ll;
    for(int num = 0; num < 10; num++) ans = (ans + dp[1][num]) % mod;
    cout << ans << '\n';

}