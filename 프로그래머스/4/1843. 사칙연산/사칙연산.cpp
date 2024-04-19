#include <vector>
#include <string>
#include <memory.h>
#include <iostream>

#define INF 1e9

using namespace std;
vector<int> number;
vector<string> op;

int dp[100][100][2];

int solve(int start, int end, int isMax) {

    int & result = dp[start][end][isMax];
    if(result != 0)
        return result;

    if(start == end) {
        return (result = number[start]);
    }

    result = isMax ? -INF : INF;

    for(int i=start; i<end; i++) {
        if(op[i] == "+") {
            result = isMax ? max(result, solve(start, i, true) + solve(i + 1, end, true))
                                    : min(result, solve(start, i, false) + solve(i + 1, end, false));
        }
        else {
            result = isMax ? max(result, solve(start, i, true) - solve(i +1, end, false))
                                    : min(result, solve(start, i, false) - solve(i + 1, end, true));
        }
    }

    return result;
}

int solution(vector<string> arr) {
    for(int i=0; i<arr.size(); i++) {
        if(i % 2 == 0)
            number.push_back(stoi(arr[i]));
        else
            op.push_back(arr[i]);
    }

    memset(dp, 0, sizeof(dp));
    return solve(0, arr.size()/2, true);
}