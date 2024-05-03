#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> dp;

int solution(int n, vector<vector<int>> results) {
    dp.resize(n + 1, vector<int>(n + 1, 0));

    for(auto result: results) {
        dp[result[0]][result[1]] = 1;
    }

    for(int k=1; k<n+1; k++) {
        for(int start=1; start<n+1; start++) {
            for(int end=1; end<n+1; end++) {
                if(dp[start][k] != 0 && dp[k][end] != 0) {
                    dp[start][end] = 1;
                }
            }
        }
    }
    
    vector<int> ranking;
    int answer = 0;
    for(int i=1; i<=n; i++) {
        int count = 0;
        for(int j=1; j<=n; j++) {
            if(dp[i][j] || dp[j][i])
                count++;
        }
        if(count == n-1)
            answer++;
    }

    return answer;
}