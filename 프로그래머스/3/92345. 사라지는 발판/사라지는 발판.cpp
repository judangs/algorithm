#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Pos {
    int y;
    int x;
};

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool check(int height, int width, int y, int x) {
    return 0 <= y && y < height && 0 <= x && x < width;
}

int dfs(vector<vector<int>> & board, Pos current, Pos next) {
    if(board[current.y][current.x] == 0) return 0;

    int ret = 0;
    for(int dir=0; dir<4; dir++) {
        int ny = current.y + dy[dir];
        int nx = current.x + dx[dir];
        
        if(check(board.size(), board[0].size(), ny, nx) == false) continue;
        
        if(board[ny][nx] == 1) {
            board[current.y][current.x] = 0;
            int step = dfs(board, next, {ny, nx}) + 1;
            board[current.y][current.x] = 1;

            if(ret % 2 == 1 && step % 2 == 1) ret = min(ret, step);
            else if(ret % 2 == 0 && step % 2 == 1) ret = step;
            else if(ret % 2 == 0 && step % 2 == 0) ret = max(ret, step);
        }
    }

    return ret;
}

int solution(vector<vector<int>> board, vector<int> aloc, vector<int> bloc) {

    Pos player1 = {aloc[0], aloc[1]};
    Pos player2 = {bloc[0], bloc[1]};

    return dfs(board, player1, player2);
}