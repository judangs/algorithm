#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};

bool in_range(int y, int x, int n) {
    return 0 <= y && y < n && 0 <= x && x < n;
}

// 연결된 블록(또는 빈칸)을 BFS로 추출
vector<pair<int,int>> bfs(int sy, int sx, vector<vector<int>>& board, vector<vector<bool>>& visit, int target) {
    int n = board.size();
    queue<pair<int,int>> q;
    vector<pair<int,int>> shape;
    
    q.push({sy, sx});
    visit[sy][sx] = true;
    
    while(!q.empty()) {
        auto [y, x] = q.front();
        q.pop();
        
        shape.push_back({y, x});
        
        for(int dir = 0; dir < 4; dir++) {
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            
            if(!in_range(ny, nx, n)) continue;
            if(visit[ny][nx]) continue;
            if(board[ny][nx] != target) continue;
            
            visit[ny][nx] = true;
            q.push({ny, nx});
        }
    }
    
    return shape;
}

// 좌표를 (0,0) 기준으로 정규화
vector<pair<int,int>> normalize(vector<pair<int,int>> shape) {
    int minY = 1e9, minX = 1e9;
    
    for(auto& [y, x] : shape) {
        minY = min(minY, y);
        minX = min(minX, x);
    }
    
    for(auto& [y, x] : shape) {
        y -= minY;
        x -= minX;
    }
    
    sort(shape.begin(), shape.end());
    return shape;
}

// 90도 회전: (y, x) -> (x, -y)
vector<pair<int,int>> rotate_shape(vector<pair<int,int>> shape) {
    vector<pair<int,int>> rotated;
    
    for(auto& [y, x] : shape) {
        rotated.push_back({x, -y});
    }
    
    return normalize(rotated);
}

// 두 도형이 회전으로 일치하는지 검사
bool is_same_shape(vector<pair<int,int>> a, vector<pair<int,int>> b) {
    if(a.size() != b.size()) return false;
    
    a = normalize(a);
    b = normalize(b);
    
    for(int r = 0; r < 4; r++) {
        if(a == b) return true;
        a = rotate_shape(a);
    }
    
    return false;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int n = game_board.size();
    
    vector<vector<bool>> visit_table(n, vector<bool>(n, false));
    vector<vector<bool>> visit_board(n, vector<bool>(n, false));
    
    vector<vector<pair<int,int>>> puzzles;
    vector<vector<pair<int,int>>> blanks;
    
    // table에서 퍼즐 조각(1) 추출
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!visit_table[i][j] && table[i][j] == 1) {
                auto shape = bfs(i, j, table, visit_table, 1);
                puzzles.push_back(normalize(shape));
            }
        }
    }
    
    // game_board에서 빈칸(0) 추출
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(!visit_board[i][j] && game_board[i][j] == 0) {
                auto shape = bfs(i, j, game_board, visit_board, 0);
                blanks.push_back(normalize(shape));
            }
        }
    }
    
    int answer = 0;
    vector<bool> used(puzzles.size(), false);
    
    // 각 빈칸에 대해 아직 사용하지 않은 퍼즐 조각 중 맞는 것 찾기
    for(auto& blank : blanks) {
        for(int i = 0; i < puzzles.size(); i++) {
            if(used[i]) continue;
            if(blank.size() != puzzles[i].size()) continue;
            
            if(is_same_shape(puzzles[i], blank)) {
                used[i] = true;
                answer += blank.size();
                break;
            }
        }
    }
    
    return answer;
}