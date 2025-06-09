#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MOD 1000000007

using namespace std;

const int maxh = 5000;
int N, h;
vector<int> altar;

long long calc(vector<vector<long long>> & dp, int idx, int h) {
    long long ret = 0ll;
    if(0 <= h - 1) ret += dp[idx ^ 1][h - 1];
    if(h + 1 < maxh) ret += dp[idx ^ 1][h + 1];

    return (ret + dp[idx ^ 1][h]) % MOD;
}

int main() {


    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> h;
        altar.push_back(h);
    }

    if(altar.front() > 0 || altar.back() > 0) {
        cout << "0";
        return 0;
    }

    vector<vector<long long>> dp(2, vector<long long>(maxh, 0));
    
    dp[0][0] = 1;
    for(int idx=1; idx<N; idx++) {

        fill(dp[idx % 2].begin(), dp[idx % 2].end(), 0);

        int h = altar[idx];
        int cmaxh = min(idx, N - idx - 1);
        if(h != -1) {
            dp[idx % 2][h] = calc(dp, idx % 2, h);
        }
        else {
            int cmaxh = min(idx, N - idx - 1);
            for(int ch=0; ch<=cmaxh; ch++) {
                dp[idx % 2][ch] = calc(dp, idx % 2, ch);
            }
        }     
    }    

    cout << dp[(N % 2) ^ 1][0];
}