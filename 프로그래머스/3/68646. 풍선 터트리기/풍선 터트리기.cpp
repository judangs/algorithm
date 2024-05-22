#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> dp;

int solution(vector<int> a) {
    dp.resize(a.size(), vector<int>(2, 0));
    
    int N = a.size() - 1;
    dp[0][0] = a[0];
    dp[N][1] = a.back();
    for(int i=1; i<a.size(); i++) {
        dp[i][0] = min(dp[i - 1][0], a[i]);
        dp[N - i][1] = min(dp[N - i + 1][1], a[N - i]);
    }

    int answer = 2;
    for(int current=1; current<N; current++) {
        if(dp[current - 1][0] < a[current] && dp[current + 1][1] < a[current]) continue;
        answer++;
    }

    return answer;
}