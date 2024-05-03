#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <iostream>

#define INF 1e9

using namespace std;

vector<vector<vector<int>>> visit(25, vector<vector<int>>(25, vector<int>(2, INF)));
queue<tuple<int, int, int>> q;

static int move_y[] = {1, 0, -1, 0};
static int move_x[] = {0, -1, 0, 1};

bool check_range(int y, int x, int n) {
    return 0<=y && y<n && 0<=x && x<n;
}

int solution(vector<vector<int>> board) {

    if(board[0][1] != 1) {
        q.push(make_tuple(0, 1, 1));
        visit[0][1][1] = 100;
    }
    if(board[1][0] != 1) {
        q.push(make_tuple(1, 0, 0));
        visit[1][0][0] = 100;
    }

    while(!q.empty()) {
        int y, x, direction;
        tie(y, x, direction) = q.front();
 
        q.pop();
        int cost = visit[y][x][direction];

        for(int k=0; k<4; k++) {
            int next_y = y + move_y[k];
            int next_x = x + move_x[k];

            if(check_range(next_y, next_x, board.size()) == false) continue;
            
            if(board[next_y][next_x] != 1) {
                if((k % 2) != direction) {
                    if(cost + 600 <= visit[next_y][next_x][direction ^ 1]) {
                        visit[next_y][next_x][direction ^ 1] = cost + 600;
                        q.push(make_tuple(next_y, next_x, (direction ^ 1)));                    
                    }
                }
                else {
                    if(cost + 100 <= visit[next_y][next_x][direction]) {
                        visit[next_y][next_x][direction] = cost + 100;
                        q.push(make_tuple(next_y, next_x, direction));
                    }
                }                
            }
        }
    }

    int destination = board.size() - 1;
    return min(visit[destination][destination][0], visit[destination][destination][1]);
}