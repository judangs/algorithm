#include <string>
#include <vector>

#define DIV 10007

using namespace std;

vector<vector<int>> dp;

int solution(int n, vector<int> tops) {
    
    dp.resize(2 * n + 2, vector<int>(2, 0));
    
    dp[1][0] = 1;
    for(int cur=2; cur<dp.size(); cur++) {
        
        // 현재 위치에 삼각형을 사용하는 경우,
        dp[cur][0] += (dp[cur - 1][0] + dp[cur - 1][1]) % DIV;
        
        // 현재 위치에 마름모를 사용하는 경우, top이 붙어있을 때(위쪽 마름모)
        int top = cur / 2 - 1;
        if(cur % 2 == 0 && tops[top] == 1) {
            dp[cur][1] += (dp[cur - 1][0] + dp[cur - 1][1]) % DIV;
        }
        // 현재 위치에서 마름모를 사용하는 경우, 역방향 마름모, 이전에는 마름모 사용 X
        if(cur % 2 == 1) {
            dp[cur][1] += (dp[cur - 1][0]) % DIV;
        }
        
        // 정방향 마름모
        if(cur % 2 == 0) {
            dp[cur][1] += (dp[cur - 1][0]) % DIV;
        }
    }
    
    int back = 2 * n + 1;
    return (dp[back][0] + dp[back][1]) % DIV;
}