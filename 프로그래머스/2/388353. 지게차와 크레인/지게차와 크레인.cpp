#include <string>
#include <vector>
#include <queue>

using namespace std;

int n, m;
static int dy[] = { 0, -1, 0, 1 };
static int dx[] = { 1, 0, -1, 0 };
struct Node {
    int y, x, remain;
};

bool is_valid(int y, int x) {
    return 0 <= y && y < 100 && 0 <= x && x < 100;
}

void bfs(vector<vector<char>> & board, char op) {
    
    queue<Node> q;
    vector<vector<bool>> visit(100, vector<bool>(100, false));
    q.push({ 0, 0, 1 });
    
    visit[0][0] = true;
    
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        board[node.y][node.x] = '0';
         
        for(int d = 0; d < 4; d++) {
            int ny = node.y + dy[d], nx = node.x + dx[d];
            if(is_valid(ny, nx) && !visit[ny][nx]) {
                
                if(node.remain == 1) {
                    if(board[ny][nx] == '0') {
                        visit[ny][nx] = true;
                        q.push({ ny, nx, node.remain});
                    }
                    if(board[ny][nx] == op) {
                        visit[ny][nx] = true;
                        q.push({ ny, nx, node.remain - 1 });
                    }                    
                }
            }
        }
    }
    
}

int solution(vector<string> storage, vector<string> requests) {
    
    vector<vector<char>> board(100, vector<char>(100, '0'));
    
    n = storage.size(), m = storage[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            board[25 + i][25 + j] = storage[i][j];
        }
    }
    
    for(auto & request: requests) {
        if(request.size() == 1) {
            bfs(board, request.front());
        }
        if(request.size() == 2) {
            char op = request.front();
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if(board[25 + i][25 + j] == op)
                        board[25 + i][25 + j] = '0';
                }
            }
        }
    }
    
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[25 + i][25 + j] != '0')
                ans++;
        }
    }
    
    return ans;
}