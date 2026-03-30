#include <string>
#include <vector>

using namespace std;

static int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };
static int dx[] = { 1, 0, -1, 0, 1, -1, 1, -1 };

bool is_range(int y, int x, int n) {
    return 0 <= y && y < n && 0 <= x && x < n;
}

bool is_valid(int y, int x, int n, vector<vector<bool>> & visit) {
    
    for(int d = 0; d < 8; d++) {
        int ny = y, nx = x;
        while(is_range(ny, nx, n)) {
            if(visit[ny][nx])
                return false;
            
            ny += dy[d], nx += dx[d];
        }
    }
    
    return true;
    
}

int dfs(int y, int n, vector<vector<bool>> & visit) {
    
    if(y == n) return 1;
    
    int ret = 0;
    for(int i = 0; i < n; i++) {
        if(is_valid(y, i, n, visit)) {
            visit[y][i] = true;
            ret += dfs(y + 1, n, visit);
            visit[y][i] = false;
        }
    }
    
    return ret;
}

int solution(int n) {
    
    vector<vector<bool>> visit(n, vector<bool>(n, false));
    int ans = dfs(0, n, visit);
    return ans;
    
}