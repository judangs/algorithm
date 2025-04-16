#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M;
vector<int> boy;
vector<int> girl;

int main() {

    cin >> N >> M;

    boy.resize(N), girl.resize(M);
    for(int i=0; i<N; i++) cin >> boy[i];
    for(int i=0; i<M; i++) cin >> girl[i];

    sort(boy.begin(), boy.end());
    sort(girl.begin(), girl.end());

    vector<vector<long long>> dp(N + 1, vector<long long>(M + 1));
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            dp[i][j] = dp[i - 1][j - 1] + abs(boy[i - 1] - girl[j - 1]);
            if(i > j) dp[i][j] = min(dp[i][j], dp[i - 1][j]);
            if(i < j) dp[i][j] = min(dp[i][j], dp[i][j - 1]);
        }
    }

    cout << dp[N][M];

}
