#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e18

using namespace std;

int T, N;
vector<long long> dp(101, INF);

int main() {

    cin >> T;
    dp[2] = 1, dp[3] = 7, dp[4] = 4, dp[5] = 2, dp[6] = 6, dp[7] = 8;
    for(int num=8; num<dp.size(); num++) {
        for(int sub=2; sub<=7; sub++) {
            if(num - sub >= 0 && dp[num - sub] != INF) {
                if(sub == 6) {
                    dp[num] = min(dp[num], (10 * dp[num - sub]));    
                }
                else {
                    dp[num] = min(dp[num], (10 * dp[num - sub]) + dp[sub]);    
                }
            }
        }
    }

    while(T--) {
        cin >> N;

        int current = N;
        string answer = "";
        if(N % 2 != 0) {
            answer += '7';
            current -= 3;
        }

        answer += string(current / 2, '1');
        cout << dp[N] << " " << answer << "\n";
        
    }
}