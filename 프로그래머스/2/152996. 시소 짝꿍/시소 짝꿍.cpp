#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

long long solution(vector<int> weights) {
    
    vector<int> dp(1001, 0);
    sort(weights.begin(), weights.end());
    
    for(int weight: weights) {
        dp[weight]++;
    }
    
    long long answer = 0;
    for(int i=0; i<weights.size(); i++) {
        if(weights[i] % 2 == 0) {
            int pair = weights[i] / 2 * 3;
            if(pair <= 1000)
                answer += dp[pair];
        }
        
        if(weights[i] % 3 == 0) {
            int pair = weights[i] / 3 * 4;
            if(pair <= 1000)
                answer += dp[pair];
        }

        if(weights[i] * 2 <= 1000) {
            int pair = weights[i] * 2;
            answer += dp[pair];
        }
    }

    for(int i=100; i<1001; i++) {
        if(dp[i] >= 2) {
            answer += (pow(dp[i], 2) - dp[i]) / 2;
        }
    }
    
    return answer;
}