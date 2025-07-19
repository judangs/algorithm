#include <iostream>

#define INF 1e18

using namespace std;
typedef long long ll;

int N, K;
ll dp[801][4001];
int relation[4001][4001];
ll awkward[4001][4001];

void DnC(int train, int l, int r, int optl, int optr) {

    if(l > r) return;
    int m = (l + r) / 2;
    
    ll mincost = INF, opt = -1;
    for(int k=optl; k<=min(m - 1, optr); k++) {
        ll cost = dp[train - 1][k] + awkward[k + 1][m];
        if(cost < mincost) {
            mincost = cost; opt = k;
        }
    }

    dp[train][m] = mincost;
    DnC(train, l, m - 1, optl, opt);
    DnC(train, m + 1, r, opt, optr);
    
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K;

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            int u; cin >> u;
            relation[i][j] = u;
        }
    }


    for(int i=1; i<=N; i++) {
        for(int j=2; j<=N; j++) {
            relation[i][j] += relation[i][j - 1];
        }
    }
    
    for(int i=1; i<=N; i++) {
        awkward[i][i] = 0;
        for(int j=i+1; j<=N; j++) {
            awkward[i][j] = awkward[i][j - 1] + relation[j][j] - relation[j][i - 1];
        }
    }

    for(int i=1; i<=N; i++) dp[1][i] = awkward[1][i];
    for(int train=2; train<=K; train++) DnC(train, train, N, train - 1, N - 1);

    cout << dp[K][N] << endl;

}