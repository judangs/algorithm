#include <iostream>
#include <vector>
#include <memory.h>
#include <stdlib.h>

#define INF 1e9

using namespace std;

int N, M, X;

vector<vector<char>> board;
int cache[51][51][4];
bool visited[51][51];

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool valid(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}

int move(int y, int x, int dir) {

    if(!valid(y, x)) return 0;
    if(board[y][x] == 'H') return 0;
    if(visited[y][x]) {
        cout << "-1";
        exit(0);
    }

    int & ret = cache[y][x][dir];
    if(ret != 0) return ret;

    visited[y][x] = true;
    
    ret = 0;
    for(int dir=0; dir<4; dir++) {
        int ny = y + dy[dir] * (board[y][x] - '0'), nx = x + dx[dir] * ((board[y][x] - '0'));
        ret = max(ret, 1 + move(ny, nx, dir));
    }

    visited[y][x] = false;

    return ret;
}


int main() {

    memset(cache, 0, sizeof(cache));
    memset(visited, false, sizeof(visited));


    cin >> N >> M;
    board.resize(N, vector<char>(M));

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> board[i][j];
        }
    }

    int answer = move(0, 0, 0);
    cout << answer;
}