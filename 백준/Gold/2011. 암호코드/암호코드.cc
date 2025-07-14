#include <iostream>
#include <cstring>
#include <vector>

#define MOD 1000000

using namespace std;

string pattern;

int main() {

    cin >> pattern;
    
    pattern = '0' + pattern;
    int n = pattern.size();
    vector<int> dp(n, 0);

    dp[0] = 1;
    for(int i=1; i<n; i++) {
        
        int alpha = pattern[i] - '0';
        if(1 <= alpha && alpha <= 9)
            dp[i] = (dp[i] + dp[i - 1]) % MOD;

        if(0 <= i - 2) {
            int c = (pattern[i - 1] - '0') * 10 + (pattern[i] - '0');
            if(10 <= c && c <= 26)
                dp[i] = (dp[i] + dp[i - 2]) % MOD;
        }
    }

    cout << dp[n - 1];
}