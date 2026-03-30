#include <string>
#include <vector>
#include <queue>

using namespace std;

static int dy[] = { 0, -1, 0, 1 };
static int dx[] = { 1, 0, -1, 0 };
int n, m;
const int inf = 1e9;
struct Position {
    int y, x;
};

Position start, ed, button;

bool is_valid(int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < m;
}

int bfs(Position pos, char opt, vector<string> & maps) {
    
    queue<pair<Position, int>> q;
    q.push({ pos, 0 });
    
    vector<vector<int>> board(n, vector<int>(m, inf));
    
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        for(int d = 0; d < 4; d++) {
            int ny = node.first.y + dy[d], nx = node.first.x + dx[d];
            if(is_valid(ny, nx) && maps[ny][nx] != 'X') {
                if(node.second + 1 < board[ny][nx]) {
                    board[ny][nx] = node.second + 1;
                    q.push({ Position{ ny, nx}, board[ny][nx] });
                }
            }
        }
    }
    
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(maps[i][j] == opt)
                return board[i][j];
        }
    }
    
    return 0;
    
}

int solution(vector<string> maps) {
    
    n = maps.size(), m = maps[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(maps[i][j] == 'S') { start =  Position {i, j }; }
            if(maps[i][j] == 'E') { ed = Position { i, j }; }
            if(maps[i][j] == 'L') { button = Position { i, j }; }
        }
    }
    
    int ans = bfs(start, 'L', maps);
    if(ans != inf) {
        int next = bfs(button, 'E', maps);
        if(next != inf) return (ans + next);
        return -1;
    }
    
    return -1;
    
}