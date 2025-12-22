#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int N;
vector<int> times;
int dp[200005];

int parse(string clock) {
    return (60 * stoi(clock.substr(0, clock.find(':')))
        + stoi(clock.substr(clock.find(':') + 1)));
}

int solve(int idx) {
    if(idx >= N) return 0;
    if(dp[idx] != -1) return dp[idx];
    
    int ret = 1e9;
    
    for(int cnt = 1; cnt <= 3 && idx + cnt <= N; cnt++) {
        if(times[idx + cnt - 1] - times[idx] <= 20) {
            ret = min(ret, 1 + solve(idx + cnt));
        }
    }
    
    return dp[idx] = ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N;
    times.resize(N);
    
    for(auto & time: times) {
        string clock; 
        cin >> clock;
        time = parse(clock);
    }
    
    sort(times.begin(), times.end());
    memset(dp, -1, sizeof(dp));
    
    cout << solve(0) << endl;

}