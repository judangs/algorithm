#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, H;
int board[10][10];
vector<pair<int, int>> milks;
pair<int, int> home;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> N >> M >> H;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> board[i][j];
            if (board[i][j] == 1) {
                home = {i, j};
            } else if (board[i][j] == 2) {
                milks.push_back({i, j});
            }
        }
    }
    
    sort(milks.begin(), milks.end());
    
    int answer = 0;
    
    do {

        auto now = home; int health = M;
        for (int i = 0; i < milks.size(); i++) {
            auto [cy, cx] = milks[i];
            int distance = abs(now.first - cy) + abs(now.second - cx);
            
            if (distance <= health) {

                health = health - distance + H;
                now = {cy, cx};
                
                int home_distance = abs(cy - home.first) + abs(cx - home.second);
                if (home_distance <= health) {
                    answer = max(answer, i + 1);
                }
            } else {
                break;
            }
        }
        
    } while (next_permutation(milks.begin(), milks.end()));

    cout << answer << endl;
    
}