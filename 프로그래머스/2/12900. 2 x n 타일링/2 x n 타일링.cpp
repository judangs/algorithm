#include <string>
#include <vector>

#define DIV 1000000007

using namespace std;

vector<int> dp;

int solution(int n) {    

    dp.resize(n + 1, 0);
    dp[1] = 1;
    dp[2] = 2;

    for(int current=3; current < dp.size(); current++) {
        dp[current] = (dp[current - 1] + dp[current - 2]) % DIV;
    }
    
    return dp[n];
}