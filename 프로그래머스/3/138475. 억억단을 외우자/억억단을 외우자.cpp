#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> arr, dp;

vector<int> solution(int e, vector<int> starts) {
    arr.resize(e + 1, 0);
    for(int i=1; i<=e; i++) {
        for(int j=i; j<=e; j += i) {
            arr[j]++; 
        }
    }

    dp.resize(e + 1, 0);
    dp[e] = e;
    for(int i=e - 1; i > 0; i--) {
        if(arr[dp[i + 1]] <= arr[i]) {
            dp[i] = i;
        }
        else {
            dp[i] = dp[i + 1];
        }
    }

    vector<int> answer;
    for(int start: starts) {
        answer.push_back(dp[start]);
    }

    return answer;
}