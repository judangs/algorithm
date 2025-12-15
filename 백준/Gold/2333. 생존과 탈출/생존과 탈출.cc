#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL);

using namespace std;
int D, G;
struct Food {
    int t, f, h; 
};
vector<Food> foods;
int dp[101][3001];

const int inf = 1e9;

int main() {

    fastio;
    memset(dp, -1, sizeof(dp));

    cin >> D >> G;
    foods = vector<Food>(G + 1);
    foods[0] = {0, 0, 0};
    for(int i = 1; i <= G; i++) {
        auto & food = foods[i];
        cin >> food.t >> food.f >> food.h;
    }
    
    sort(foods.begin(), foods.end(), [](const Food & l, const Food & r) {
        return l.t < r.t;
    });

    dp[0][0] = 10;

    int answer = inf;
    for(int i = 1; i <= G; i++) {
        for(int h=0; h <= 3000; h++) {
            if(dp[i - 1][h] == -1) continue;

            int damage = (foods[i].t - foods[i - 1].t);
            if(0 <= dp[i - 1][h] - damage) {
                dp[i][h + foods[i].h] = max(dp[i][h + foods[i].h], dp[i - 1][h] - damage);
                if(D <= h + foods[i].h) {
                    answer = min(answer, foods[i].t);
                }
            }

            if(0 <= dp[i - 1][h] - damage) {
                dp[i][h] = max(dp[i][h], dp[i - 1][h] - damage + foods[i].f);
            }
        }
    }

    if(answer == inf) {
        answer = 10;
        for(int i = 1; i <= G; i++) {
            for(int h = 0; h <= 3000; h++) {
                if(0 <= dp[i][h]) {
                    answer = max(answer, dp[i][h] + foods[i].t);
                }
            }
        }
    }

    cout << answer << endl;

}