#include <vector>
#include <iostream>

using namespace std;


int solution(int m, int n, vector<vector<int>> city_map) {

    int MOD = 20170805;

    int dp[501][501][2] = {0, };
    dp[0][0][0] = 1;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(city_map[i][j] == 0) {
                dp[i + 1][j][0] += (dp[i][j][0] + dp[i][j][1]) % MOD;
                dp[i][j + 1][1] += (dp[i][j][0] + dp[i][j][1]) % MOD;
            }

            if(city_map[i][j] == 1) continue;
            
            if(city_map[i][j] == 2) {
                dp[i + 1][j][0] += dp[i][j][0];
                dp[i + 1][j][0] %= MOD;
                dp[i][j + 1][1] += dp[i][j][1];
                dp[i][j + 1][1] %= MOD;
            }
        }
    }

    int answer = (dp[m-1][n-1][0] + dp[m-1][n-1][1]) % MOD;
    return answer;
}