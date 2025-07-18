#include <iostream>
#include <vector>
#include <memory.h>

#define MAXPROBLEM 150
#define MAXSCORE 1132500

using namespace std;
typedef unsigned long long ll;

int N, K;
vector<int> problem;
vector<int> psum;

ll dp[MAXPROBLEM + 1][20000];
int solved[MAXPROBLEM + 1][MAXPROBLEM + 1];


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    memset(dp, 0, sizeof(dp));
    
    cin >> N;
    problem.resize(N + 1);
    psum.resize(N + 1, 0);

    for(int i = 1; i <= N; i++) {
        cin >> problem[i];
        psum[i] = psum[i - 1] + problem[i];
    }

    for(int i=1; i<=N; i++) {
        for(int j=i; j<=N; j++) {
            if(i == j) solved[i][j] = problem[i];
            else
                solved[i][j] = solved[i][j - 1] + psum[j] - psum[i - 1];
        }
    }

    cin >> K;
    if(K > MAXSCORE) {
        cout << K << endl;
        return 0;
    }

    dp[0][0] = 1ll;
    
    for(int right = 1; right <= N; right++) {
        for(int left = 1; left <= right; left++) {


            for(int block = 0; block < 20000; block++) {

                int next = solved[left][right] / 64, bit = solved[left][right] % 64;

                if(left == 1) {
                    dp[right][block] = dp[right - 1][block];
                    dp[right][next] |= (1ll << bit);
                }
                else {
                    if(bit == 0) {
                        if(block + next < 20000) dp[right][block + next] |= dp[left - 2][block];
                    }
                    else {
                        if(block + next < 20000) dp[right][block + next] |= (dp[left - 2][block] << bit);
                        if(block + next + 1 < 20000) dp[right][block + next + 1] |= (dp[left - 2][block] >> (64 - bit));
                        
                    }
                }
            }
        }
    }

    while(K <= MAXSCORE && K / 64 < 20000) {
        if(!(dp[N][K / 64] & (1ll << (K % 64)))) break;
        K++;
    }

    cout << K << endl;

}