#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> dp;

int solution(int m, int n, vector<vector<int>> puddles) {
    dp.resize(n + 1, vector<int>(m + 1, 0));
    
    for(int i=1; i<m+1; i++)
        dp[1][i] = 1;
    for(int j=1; j<n+1; j++)
        dp[j][1] = 1;
    
    for(auto puddle: puddles) {
        dp[puddle[1]][puddle[0]] = -1;
        if(puddle[1] == 1) {
            for(int i=puddle[0]; i<m+1; i++)
                dp[1][i] = -1;
        }
        else if(puddle[0] == 1) {
            for(int i=puddle[1]; i<n+1; i++)
                dp[i][1] = -1;
        }
    }
    
    for(int i=2; i<n+1; i++) {
        for(int j=2; j<m+1; j++) {
            if(dp[i][j] == -1) continue;
            
            if(dp[i-1][j] != -1)
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % 1000000007;
            if(dp[i][j-1] != -1)
                dp[i][j] = (dp[i][j] + dp[i][j-1]) % 1000000007;
        }
    }
    
    return dp[n][m];
}