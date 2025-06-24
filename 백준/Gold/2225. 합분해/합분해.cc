#include <iostream>
#include <vector>

#define MOD 1000000000

using namespace std;
typedef long long ll;

int N, K;
vector<vector<ll>> dp;

int main() {

    cin >> N >> K;
    dp.resize(N + 1, vector<ll>(K + 1, 0ll));
    
    for(int num=0; num<=N; num++) dp[num][1] = 1ll;

    for(int k=2; k<=K; k++) {
        for(int num=0; num <= N; num++) {
            for(int use=0; use<=N; use++) {
                if(num + use <= N) dp[num + use][k] = (dp[num + use][k] + dp[num][k - 1]) % MOD;
            }
        }
    }

    cout << dp[N][K];

}