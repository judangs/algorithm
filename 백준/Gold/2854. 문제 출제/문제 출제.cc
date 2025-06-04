#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7;
int N, P;
ll dp[2][100001];
vector<int> A, B;


int main() {

    memset(dp, 0, sizeof(dp));

    cin >> N;

    A.resize(N + 1), B.resize(N);
    for(int idx=1; idx<=N; idx++) cin >> A[idx];
    for(int idx=1; idx<N; idx++) cin>> B[idx];

    dp[0][1] = A[1], dp[1][1] = B[1];
    for(int score=2; score<=N; score++) {
        dp[0][score] = (dp[0][score - 1] * (A[score] + B[score - 1]) + dp[1][score - 1] * A[score]) % MOD;
        if(B[score - 1] - 1 >= 0) dp[0][score] = (dp[0][score] + dp[1][score - 1] * (B[score - 1] - 1)) % MOD;
        if(score < N) dp[1][score] = ((dp[0][score - 1] + dp[1][score - 1]) * B[score]) % MOD;
    }

    cout << dp[0][N];

}