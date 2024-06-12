#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> pulse;
vector<vector<long long>> dp;

long long solution(vector<int> sequence) {
    pulse.resize(2, vector<int>(sequence.size(), 0));
    dp.resize(sequence.size() + 1, vector<long long>(2, 0));

    for(int i=0; i<sequence.size(); i++) {
        if(i % 2 == 0 || i == 0) pulse[0][i] = 1;
        else pulse[0][i] = -1;
    }

    for(int i=0; i<sequence.size(); i++) {
        if(i % 2 == 0 || i == 0) pulse[1][i] = -1;
        else pulse[1][i] = 1;
    }

    dp[0][0] = sequence[0] * pulse[0][0];
    dp[0][1] = sequence[0] * pulse[1][0];

    long long answer = max(dp[0][0], dp[0][1]);
    for(int i=0; i<sequence.size()-1; i++) {
        dp[i + 1][0] = max((long long) (sequence[i + 1] * pulse[0][i + 1]), dp[i][0] + (long long )(sequence[i + 1] * pulse[0][i + 1]));
        dp[i + 1][1] = max((long long)(sequence[i + 1] * pulse[1][i + 1]), dp[i][1] + (long long)(sequence[i + 1] * pulse[1][i + 1]));
        
        answer = max(answer, dp[i + 1][0]);
        answer = max(answer, dp[i + 1][1]);
    }

    return answer;
}