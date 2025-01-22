#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int board[500][500];

static int dy[] = {1, 0, -1, 0};
static int dx[] = {0, 1, 0, -1};

bool check(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}

int dfs(int depth, int y, int x, vector<vector<bool>> & visit, int cost) {
    if(depth == 4) {
        return cost;
    }
    
    int ret = 0;
    for(int dir=0; dir<4; dir++) {
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        
        if(check(ny, nx) == false) continue;
        if(visit[ny][nx] == false) {
            visit[ny][nx] = true;
            ret = max(ret, dfs(depth + 1, y, x, visit, cost + board[ny][nx]));
            ret = max(ret, dfs(depth + 1, ny, nx, visit, cost + board[ny][nx]));
            visit[ny][nx] = false;
        }
    }
    
    return ret;
}


int main() {
    cin >> N >> M;
    
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> board[i][j];
        }
    }
    
    int answer = 0;
    vector<vector<bool>> visit(N, vector<bool>(M, false));
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            visit[i][j] = true;
            answer = max(answer, dfs(1, i, j, visit, board[i][j]));
            visit[i][j] = false;
        }
    }
    
    cout << answer;
}