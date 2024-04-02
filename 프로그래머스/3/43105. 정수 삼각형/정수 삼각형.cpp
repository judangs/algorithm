#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> dp;

int solution(vector<vector<int>> triangle) {
    
    int depth = triangle.size();
    dp.resize(depth, vector<int>(depth, 0));

    dp[0][0] = triangle[0][0];
    
    for(int i=0; i<depth-1; i++) {
        for(int j=0; j<=i; j++) {
            dp[i + 1][j] = max(dp[i + 1][j], dp[i][j] + triangle[i + 1][j]);
            dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + triangle[i + 1][j + 1]);
        }
    }

    int answer = 0;
    for(int i=0; i<depth; i++) {
        answer = max(answer, dp[depth - 1][i]);
    }
    return answer;
}