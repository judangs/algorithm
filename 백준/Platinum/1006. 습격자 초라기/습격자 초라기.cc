#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e9

using namespace std;

int T, N, W;

int dp(vector<vector<int>> & enemy, bool top, bool bottom) {

    vector<int> up(N + 1, INF);
    vector<int> down(N + 1, INF);
    vector<int> both(N + 1, INF);

    both[0] = 0;
    up[1] = 1, down[1] = 1, both[1] = 2;
    if(enemy[0][1] + enemy[1][1] <= W) both[1] = 1;


    for(int idx=2; idx<=N; idx++) {
        up[idx] = min(up[idx], both[idx - 1] + 1);
        if(enemy[0][idx] + enemy[0][idx - 1] <= W) up[idx] = min(up[idx], down[idx - 1] + 1);

        down[idx] = min(down[idx], both[idx - 1] + 1);
        if(enemy[1][idx] + enemy[1][idx - 1] <= W) down[idx] = min(down[idx], up[idx - 1] + 1);

        both[idx] = min({both[idx], up[idx] + 1, down[idx] + 1, both[idx - 1] + 2});
        if(enemy[0][idx] + enemy[1][idx] <= W) both[idx] = min(both[idx], both[idx - 1] + 1);
        if(enemy[0][idx] + enemy[0][idx - 1] <= W && enemy[1][idx] + enemy[1][idx - 1] <= W) {
            both[idx] = min(both[idx], both[idx - 2] + 2);
        }
    }

    if(N == 1) return both[1];
    if(!top && !bottom) return both[N];
    if(top && !bottom) return down[N];
    if(!top && bottom) return up[N];
    if(top && bottom) return both[N - 1];
    
    return 0;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {
        cin >> N >> W;

        vector<vector<int>> enemy(2, vector<int>(N + 1));
        for(int i=0; i<2; i++) {
            for(int j=1; j<=N; j++) {
                cin >> enemy[i][j];
            }
        }

        int answer = INF;

        answer = min(answer, dp(enemy, false, false));
        if(enemy[0][1] + enemy[0][N] <= W) {
            int tmp1 = enemy[0][1], tmp2 = enemy[0][N];
            enemy[0][1] = W, enemy[0][N] = W;
            answer = min(answer, dp(enemy, true, false));
            enemy[0][1] = tmp1, enemy[0][N] = tmp2;
        }
        if(enemy[1][1] + enemy[1][N] <= W) {
            int tmp1 = enemy[1][1], tmp2 = enemy[1][N];
            enemy[1][1] = W, enemy[1][N] = W;
            answer = min(answer, dp(enemy, false, true));
            enemy[1][1] = tmp1, enemy[1][N] = tmp2;
        }
        if(enemy[0][1] + enemy[0][N] <= W && enemy[1][1] + enemy[1][N] <= W) {
            int tmp1 = enemy[0][1], tmp2 = enemy[0][N], tmp3 = enemy[1][1], tmp4 = enemy[1][N];
            enemy[0][1] = W, enemy[0][N] = W, enemy[1][1] = W, enemy[1][N] = W;
            answer = min(answer, dp(enemy, true, true));
            enemy[0][1] = tmp1, enemy[0][N] = tmp2, enemy[1][1] = tmp3, enemy[1][N] = tmp4;
        }

        cout << answer << "\n";
        
    }
    
}