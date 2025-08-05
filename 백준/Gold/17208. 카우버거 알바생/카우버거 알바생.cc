#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;

struct Food {
    int burger;
    int fried;
};
Food foods[101];

void init(vector<vector<vector<int>>> & table, int now) {
    for(int i=0; i<301; i++)
        for(int j=0; j<301; j++)
            table[now][i][j] = 0;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> K;
    for(int i=1; i<=N; i++) {
        int x, y; cin >> x >> y;
        foods[i] = {x, y};
    }

    vector<vector<vector<int>>> dp(2, vector<vector<int>>(301, vector<int>(301, 0)));
    for(int receipt=1; receipt<=N; receipt++) {

        init(dp, receipt % 2);

        for(int cheese=0; cheese <=M; cheese++) {
            for(int fried=0; fried <= K; fried++) {
                Food & need = foods[receipt];
                if(0 <= cheese - need.burger && 0 <= fried - need.fried)
                    dp[receipt % 2][cheese][fried] = max(dp[(receipt - 1) % 2][cheese][fried], dp[(receipt - 1) % 2][cheese - need.burger][fried - need.fried] + 1);
                else
                    dp[receipt % 2][cheese][fried] = max(dp[receipt % 2][cheese][fried], dp[(receipt - 1) % 2][cheese][fried]);
            }
        }
    }

    int answer = dp[N % 2][M][K];
    cout << answer << endl;

}