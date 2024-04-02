#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<long long> dp;


long long solution(int n) {
    dp.resize(2001);
    
    dp[1] = 1;
    dp[2] = 2;
    
    for(int i=3; i<dp.size(); i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % 1234567;
    }
    return dp[n] % 1234567;
}