#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<vector<int>> dp;

int solution(int alp, int cop, vector<vector<int>> problems) {
    
    int max_alp = 0, max_cop = 0;
    for(vector<int> problem: problems) {
        max_alp = max(max_alp, problem[0]);
        max_cop = max(max_cop, problem[1]);
    }
    
    if(alp >= max_alp)
        alp = max_alp;
    if(cop >= max_cop)
        cop = max_cop;
    
    dp.resize(max_alp + 3, vector<int>(max_cop + 3, INT32_MAX));
    dp[alp][cop] = 0;
    
    for(int i=alp; i<=max_alp; i++) {
        for(int j=cop; j<=max_cop; j++) {
            dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + 1);
            dp[i][j + 1] = min(dp[i][j + 1], dp[i][j] + 1);
            
            for(int k=0; k<problems.size(); k++) {
                if(i >= problems[k][0] && j >= problems[k][1]) {
                    int next_alp = min(i + problems[k][2], max_alp);
                    int next_cop = min(j + problems[k][3], max_cop);
                    dp[next_alp][next_cop] = min(dp[next_alp][next_cop], dp[i][j] + problems[k][4]);
                }
            }
        }
    }
    
    return dp[max_alp][max_cop];
}