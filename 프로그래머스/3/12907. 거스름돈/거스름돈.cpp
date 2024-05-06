#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define DIV 1000000007

using namespace std;

vector<int> dp;

int solution(int n, vector<int> money) {
    dp.resize(n + 1, 0);

    dp[0] = 1;
    for(auto m: money) {
        for(int current=m; current<=n; current++) {
            dp[current] = (dp[current] + dp[current - m]) % DIV;
        }
    }

    return dp[n];
}