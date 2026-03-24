#include <string>
#include <vector>
#include <memory.h>

using namespace std;

const int inf = 1e9;
int dp[41][121][121];

int steal(int idx, int a, int b, int n, int m, vector<vector<int>> info) {
    
    if(idx == info.size()) {
        if(a < n && b < m) {
            return a;
        }
        return inf;
    }
    
    int & ret = dp[idx][a][b];
    if(ret != -1) return ret;
    
    ret = inf;
    ret = min(ret, steal(idx + 1, info[idx].front() + a, b, n, m, info));
    ret = min(ret, steal(idx + 1, a, info[idx].back() + b, n, m, info));
    
    return ret;
    
}

int solution(vector<vector<int>> info, int n, int m) {
    
    memset(dp, -1, sizeof(dp));
    int ans = steal(0, 0, 0, n, m, info);
    return (ans == inf ? -1 : ans);
    
}