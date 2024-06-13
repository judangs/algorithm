#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <iostream>

#define INF 1e9

using namespace std;

int answer = INF;

static int dy[] = {1, 0, -1, 0};
static int dx[] = {0, 1, 0, -1};


bool check_range(int y, int x) {
    return 0<= y && y < 4 && 0 <= x && x < 4;
}

int bfs(vector<vector<int>> & board, int s_y, int s_x, int e_y, int e_x) {
    queue<tuple<int, int, int>> q;
    vector<vector<int>> distance;
    distance.resize(4, vector<int>(4, INT32_MAX));
    
    q.push({s_y, s_x, 0});
    distance[s_y][s_x] = 0;
    while(!q.empty()) {
        int c_y, c_x, cost;
        tie(c_y, c_x, cost) = q.front();

        q.pop();

        if(distance[c_y][c_x] < cost) continue;

        for(int k=0; k<4; k++) {
            int n_y = c_y + dy[k];
            int n_x = c_x + dx[k];
            
            if(check_range(n_y, n_x) == false) continue;
            if(cost + 1 < distance[n_y][n_x]) {
                distance[n_y][n_x] = cost + 1;
                q.push({n_y, n_x, cost + 1});
            }

            int ctrl_y = n_y;
            int ctrl_x = n_x;
            while(board[ctrl_y][ctrl_x] == 0) {
                if(check_range(ctrl_y + dy[k], ctrl_x + dx[k]) == true) {
                    ctrl_y += dy[k];
                    ctrl_x += dx[k];
                }
                else
                    break;
            }
            
            if(cost + 1 < distance[ctrl_y][ctrl_x]) {
                distance[ctrl_y][ctrl_x] = cost + 1;
                q.push({ctrl_y, ctrl_x, cost + 1});
            }
        }
    }

    return distance[e_y][e_x];
}

int dfs(vector<vector<int>> & board, int r, int c) {
    
    int ret = INF;
    for(int number=1; number<=6; number++) {
        vector<pair<int, int>> card;
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                if(board[i][j] == number) card.push_back({i, j});
            }
        }

        if(card.empty()) continue;
        
        int first_step = bfs(board, r, c, card[0].first, card[0].second) + bfs(board, card[0].first, card[0].second, card[1].first, card[1].second) + 2;
        int second_step = bfs(board, r, c, card[1].first, card[1].second) + bfs(board, card[1].first, card[1].second, card[0].first, card[0].second) + 2;

        board[card[0].first][card[0].second] = 0;
        board[card[1].first][card[1].second] = 0;

        ret = min(ret, first_step + dfs(board, card[1].first, card[1].second));
        ret = min(ret, second_step + dfs(board, card[0].first, card[0].second));

        board[card[0].first][card[0].second] = number;
        board[card[1].first][card[1].second] = number;

    }

    if(ret == INF) return 0;
    return ret;    
}

int solution(vector<vector<int>> board, int r, int c) {
    int answer = dfs(board, r, c);
    return answer;
}