#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<char>> board;
int answer = 0;

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool check(int y, int x) {
    return 0 <= y && y < 5 && 0 <= x && x < 5;
}

bool bfs(vector<vector<bool>> & visit, int y, int x) {
    
    queue<pair<int, int>> q;
    q.push({y, x});
    visit[y][x] = false;
    
    int count = 1;
    while(!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        
        q.pop();
        
        for(int k=0; k<4; k++) {
            int ny = cy + dy[k];
            int nx = cx + dx[k];
            
            if(check(ny, nx) == false) continue;
            if(visit[ny][nx]) {
                visit[ny][nx] = false;
                count++;
                q.push({ny, nx});
            }
        }
    }
    
    if(count == 7) return true;
    return false;
}

void dfs(int depth, int ptr, vector<int> & offset, vector<int> & current) {
    
    if(depth == 7) {
    
        int dasom = 0, doyeon = 0;
        vector<vector<bool>> visit(5, vector<bool>(5, false));
        for(int idx=0; idx<current.size(); idx++) {
            int y = current[idx] / 5;
            int x = current[idx] % 5;
            
            visit[y][x] = true;
            
            if(board[y][x] == 'S') dasom++;
            else doyeon++;
        }
        
        
        int sy = current.front() / 5;
        int sx = current.front() % 5;
        
        if(dasom >= 4) {
            if(bfs(visit, sy, sx) == true) answer++;
        }
        
        return;
    }
    
    for(int idx=ptr; idx < offset.size(); idx++) {
        current.push_back(offset[idx]);
        dfs(depth + 1, idx + 1, offset, current);
        current.pop_back();
    }
}


int main() {
    
    board.resize(5, vector<char>(5));
    vector<int> offset;
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            cin >> board[i][j];
            offset.push_back(5 * i + j);
        }
    }
    
    vector<int> current;
    dfs(0, 0, offset, current);
    cout << answer;
    
    
}