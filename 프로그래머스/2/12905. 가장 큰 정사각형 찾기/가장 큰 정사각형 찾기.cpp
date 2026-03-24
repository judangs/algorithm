#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool is_range(int cy, int cx, int n, int m) {
    return 0 <= cy && cy < n && 0 <= cx && cx < m;
}

int solution(vector<vector<int>> board) {
    
    int n = board.size(), m = board[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 1)
                dp[i][j] = 1;
        }
    }
    
    for(int i = 1; i < n; i++) {
        for(int j = 1; j < m; j++) {
            if(board[i][j] == 1)
                dp[i][j] = min( { dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1] } ) + 1;
        }
    }
    
    
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ans = max(ans, dp[i][j]);
        }
    }
    
    ans = pow(ans, 2);
    return ans;
    
}