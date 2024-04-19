#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int dp[1000001][2];

int solution(vector<int> money) {

    int n = money.size() - 1;

    int start = 0;
    dp[0][start] = money[start];
    dp[1][start] = dp[0][start];
    for(int house=2; house<n; house++) {
        dp[house][start] = max(dp[house-1][start], dp[house-2][start] + money[house]);
    }
    dp[n][0] = dp[n-1][0];

    start = 1;
    dp[1][start] = money[start];
    for(int house=2; house<=n; house++) {
        dp[house][start] = max(dp[house-1][start], dp[house-2][start] + money[house]);
    }

    return max(dp[n][0], dp[n][1]);
}