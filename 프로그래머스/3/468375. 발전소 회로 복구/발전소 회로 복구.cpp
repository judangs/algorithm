#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>
#include <iostream>

using namespace std;

const int inf = 1e9;

vector<vector<int>> distanced;
int samefloor[11][16][16];
vector<vector<int>> need;
vector<vector<int>> cached(( 1<< 16), vector<int>(16, -1));

struct Node {
    int y, x, cost;
};
static int dy[] = { 0, -1, 0, 1 };
static int dx[] = { 1, 0, -1, 0 };

int dfs(int depth, int mask, int idx, int k, int f, int y, int x, vector<vector<int>> & panels, vector<bool> & active) {
    
    if(depth == k) return 0;
    int & ret = cached[mask][idx];
    if(ret != -1) return ret;
    
    ret = inf;
    
    for(int i = 0; i < k; i++) {
        if(i == idx) continue;
        if(!active[i]) {
            bool is_required = false;
            for(int j = 0; j < need[i].size(); j++)
                if(!active[need[i][j]])
                    is_required = true;
            
            if(is_required) continue;
            
            int nf = panels[i][0], ny = panels[i][1], nx = panels[i][2];
            active[i] = true;
            
            if(f == nf) {                
                ret = min(ret, dfs(depth + 1, mask | (1 << i), i, k, nf, ny, nx, panels, active) + samefloor[nf][idx][i]);
            }
            
            int ncost = (distanced[y][x] + abs(nf - f) + distanced[ny][nx]);
            ret = min(ret, dfs(depth + 1, mask | (1 << i), i, k, nf, ny, nx, panels, active) 
                      + ncost);
            
            active[i] = false;
        }
    }
    
    return ret;
    
}

bool is_valid(int y, int x, int n, int m) {
    return 0 <= y && y < n && 0 <= x && x < m;
}


void bfs(int sy, int sx, vector<string> & grid) {
    
    int n = distanced.size(), m = distanced[0].size();
    
    queue<Node> q;
    distanced[sy][sx] = 0; q.push({ sy, sx, 0 });
    
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        for(int dir = 0; dir < 4; dir++) {
            int ny = node.y + dy[dir], nx = node.x + dx[dir];
            if(is_valid(ny, nx, n, m) && grid[ny][nx] != '#') {
                if(node.cost + 1 < distanced[ny][nx]) {
                    distanced[ny][nx] = node.cost + 1;
                    q.push({ ny, nx, distanced[ny][nx] });
                }
            }
        }
    }
}

int same(int h, int a, int b, vector<string> & grid, vector<vector<int>> & panels) {
    
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> d(n, vector<int>(m, inf));
    
    int sy = panels[a][1], sx = panels[a][2];
    
    queue<Node> q;
    d[sy][sx] = 0; q.push({ sy, sx, 0 });
    
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        for(int dir = 0; dir < 4; dir++) {
            int ny = node.y + dy[dir], nx = node.x + dx[dir];
            if(is_valid(ny, nx, n, m) && (grid[ny][nx] != '#')) {
                if(node.cost + 1 < d[ny][nx]) {
                    d[ny][nx] = node.cost + 1;
                    q.push({ ny, nx, d[ny][nx] });
                }
            }
        }
    }
    
    int ey = panels[b][1], ex = panels[b][2];
    return d[ey][ex];
    
    
}

int solution(int h, vector<string> grid, vector<vector<int>> panels, vector<vector<int>> seqs) {
    
    int n = grid.size(), m = grid[0].size();
    int ey, ex;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '@') {
                ey = i, ex = j;
                break;
            }
        }
    }
    
    distanced = vector<vector<int>>(n, vector<int>(m, inf));
    bfs(ey, ex, grid);
    
    int k = panels.size();
    for(auto & panel: panels) {
        panel[0]--, panel[1]--, panel[2]--;
    }
    vector<vector<int>> floor(11);
    for(int i = 0; i < k; i++) floor[panels[i][0]].push_back(i);
    
    for(int h = 0; h < 11; h++) {
        for(int i = 0; i < floor[h].size(); i++) {
            for(int j = i + 1; j < floor[h].size(); j++) {
                
                int a = floor[h][i], b = floor[h][j];
                int d = same(h, a, b, grid, panels);
                samefloor[h][a][b] = d;
                samefloor[h][b][a] = d;
            }
        }
    }
    
    
    need = vector<vector<int>> (k);
    for(auto & seq: seqs) {
        int front = seq.front(), back = seq.back();
        front--, back--;
        need[back].push_back(front);
    }
    
    vector<bool> active(k, false);
    if(need[0].empty()) active[0] = true;
    int ans = dfs((active[0] ? 1 : 0), (active[0] ? 1 : 0),0, k, panels[0][0], panels[0][1], panels[0][2], panels, active);
    return ans;
    
}