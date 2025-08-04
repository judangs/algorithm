#include <iostream>
#include <memory.h>
#include <algorithm>

using namespace std;

int N;
int dp[5001][10][10][10];
int temp[5001];

int click(int now, int target) {
    int direct = abs(target - now);
    int circular = 10 - direct;
    return min(direct, circular);
}

int cooking(int d, int a, int b, int c) {
    
    if(d == N) return 0;
    int & ret = dp[d][a][b][c];
    if(ret != -1) return ret;

    ret = 1e9;

    int & t = temp[d];
    ret = min({ret, cooking(d + 1, t, b, c) + click(a, t), 
                    cooking(d + 1, a, t, c) + click(b, t), 
                    cooking(d + 1, a, b, t) + click(c, t)
    });

    return ret;
}

int main() {

    memset(dp, -1, sizeof(dp));

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int i=0; i<N; i++) cin >> temp[i];

    int answer = cooking(0, 0, 0, 0);
    cout << answer << endl;

}