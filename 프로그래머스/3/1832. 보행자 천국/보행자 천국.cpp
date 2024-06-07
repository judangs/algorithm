#include <vector>
#include <iostream>

using namespace std;

int solution(int m, int n, vector<vector<int>> city_map) {

    int MOD = 20170805;

    int dp[501][501][2] = {0, };

    // 0 세로, 1 가로;
    static int dx[] = {0, 1};
    static int dy[] = {1, 0};


    dp[0][1][1] = 1;
    dp[1][0][0] = 1;

    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            for(int k=0; k<2; k++) {
                if(city_map[i][j] == 1) continue;
                if(city_map[i][j] == 0) {
                    dp[i + dy[k]][j + dx[k]][k] = (dp[i + dy[k]][j + dx[k]][k] + dp[i][j][k]) % MOD;
                    dp[i + dy[k ^ 1]][j + dx[k ^ 1]][k ^ 1] = (dp[i + dy[k ^ 1]][j + dx[k ^ 1]][k ^ 1] + dp[i][j][k]) % MOD;
                }                
                if(city_map[i][j] == 2) {
                    dp[i + dy[k]][j + dx[k]][k] = (dp[i + dy[k]][j + dx[k]][k] + dp[i][j][k]) % MOD;
                }
            }
        }
    }

    int answer = (dp[m-1][n-1][0] + dp[m-1][n-1][1]) % MOD;
    return answer;
}