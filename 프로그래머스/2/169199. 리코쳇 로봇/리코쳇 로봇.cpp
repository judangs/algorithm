#include <string>
#include <vector>

using namespace std;

const int inf = 1e9;
int n, m;
struct Position {
    int y, x;
};
Position st, ed;

Position move(Position now, int dir, vector<string> & board) {
    int i;
    if(dir == 0) {
        for(i = now.y; 0 < i; i--) {
            if(board[i - 1][now.x] != 'D') continue;
            break;
        }
        
        return Position { i, now.x };
    }
    if(dir == 1) {
        for(i = now.x; i < m - 1; i++) {
            if(board[now.y][i + 1] != 'D') continue;
            break;
        }
        
        return Position { now.y, i };
    }
    if(dir == 2) {
        for(i = now.y; i < n - 1; i++) {
            if(board[i + 1][now.x] != 'D') continue;
            break;
        }
        
        return Position { i, now.x };
    }
    
    for(i = now.x; 0 < i; i--) {
        if(board[now.y][i - 1] != 'D') continue;
        break;
    }

    return Position { now.y, i };    
}

void dfs(int count, Position now, vector<vector<int>> & visit, vector<string> & board) {
    
    for(int dir = 0; dir < 4; dir++) {
        Position next = move(now, dir, board);
        if(count + 1 < visit[next.y][next.x]) {
            visit[next.y][next.x] = count + 1;
            dfs(count + 1, next, visit, board);
        }
    }
    
} 

int solution(vector<string> board) {
    
    n = board.size(), m = board[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] == 'G') ed = { i, j };
            if(board[i][j] == 'R') st = { i, j };
        }
    }
    
    vector<vector<int>> visit(n, vector<int>(m, inf));
    visit[st.y][st.x] = 0;
    dfs(0, st, visit, board);
    if(visit[ed.y][ed.x] == inf) return -1;
    return visit[ed.y][ed.x];
    
}