#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool visit[4][500][500] = { 0, };

pair<int, int> move(int dir, char node) {
    if(dir == 0) {
        if(node == 'L') return { 0, -1 };
        if(node == 'R') return { 0, 1 };
        return { -1, 0 };
    }
    if(dir == 1) {
        if(node == 'L') return { -1, 0 };
        if(node == 'R') return { 1, 0 };
        return { 0, 1 };        
    }
    if(dir == 2) {
        if(node == 'L') return { 0, 1 };
        if(node == 'R') return { 0, -1 };
        return { 1, 0 };                
    }    
    if(node == 'L') return { 1, 0 };
    if(node == 'R') return { -1, 0 };
    return { 0, -1 };                    
    
}

int direction(int dir, char node) {
    if(node == 'L')
        return (dir - 1 + 4) % 4;
    if(node == 'R')
        return (dir + 1) % 4;
    return dir;
}

int dfs(int dir, int y, int x, int n, int m, vector<string> & grid) {
    
    if(visit[dir][y][x]) return 0;
    
    visit[dir][y][x] = true;
    
    auto mv = move(dir, grid[y][x]);
    int ny = (y + mv.first + n) % n, nx = (x + mv.second + m) % m;
    int ndir = direction(dir, grid[y][x]);
    
    
    return (1 + dfs(ndir, ny, nx, n, m, grid));
    
}

vector<int> solution(vector<string> grid) {
    
    vector<int> ans;
    int n = grid.size(), m = grid[0].size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            for(int k = 0; k < 4; k++) {
                if(!visit[k][i][j]) {
                    int len = dfs(k, i, j, n, m, grid);
                    ans.push_back(len);
                }
            }
        }
    }
    
    sort(ans.begin(), ans.end());
    return ans;
    
}