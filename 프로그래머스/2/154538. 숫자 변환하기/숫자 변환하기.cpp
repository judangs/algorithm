#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#define INF 1e9

using namespace std;

vector<int> dp;

int solution(int x, int y, int n) {
    dp.resize(y+1, INF);

    dp[x] = 0;
    
    for(int current=x; current<=y; current++) {
        if(current * 2 <= y)
            dp[current * 2] = min(dp[current * 2], dp[current] + 1);
        if(current * 3 <= y)
            dp[current * 3] = min(dp[current * 3], dp[current] + 1);
        if(current + n <= y)
            dp[current + n] = min(dp[current + n], dp[current] + 1);                            
    }

    return (dp[y] != INF ? dp[y] : -1);
}