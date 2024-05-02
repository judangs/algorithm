#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> dp;

int solution(vector<vector<int>> land) {
    dp.resize(land.size(), vector<int>(4, 0));
    for(int i=0; i<4; i++) {
        dp[0][i] = land[0][i];
    }

    int depth;
    for(depth=1; depth<land.size(); depth++) {
        for(int current=0; current<4; current++) {
            for(int prev=0; prev<4; prev++) {
                if(current == prev) continue;
                dp[depth][current] = max(dp[depth][current], dp[depth-1][prev] + land[depth][current]);
            }
        }
    }

    int answer = 0;
    for(int i=0; i<4; i++) {
        answer = max(answer, dp[depth-1][i]);
    }

    return answer;
}