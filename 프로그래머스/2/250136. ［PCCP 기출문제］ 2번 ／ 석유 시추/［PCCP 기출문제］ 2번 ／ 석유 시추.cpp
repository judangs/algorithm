#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>

using namespace std;

struct Position {
    int y;
    int x;
};

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

map<int, int> area_sz;

bool check_range(int my, int mx, int y, int x) {
    return 0 <= y && y < my && 0 <= x && x < mx;
}

int bfs(vector<vector<int>> & land, vector<vector<bool>> & visit, int y, int x, int idx) {
    
    queue<Position> q;
    q.push({ y, x });
    land[y][x] = idx;
    visit[y][x] = true;
    
    int count = 0;
    
    while(!q.empty()) {
        auto now = q.front();
        q.pop();
        
        count++;
        
        for(int dir = 0; dir < 4; dir++) {
            int ny = now.y + dy[dir];
            int nx = now.x + dx[dir];
            if(check_range(land.size(), land[0].size(), ny, nx)) {
                if(land[ny][nx] == 1 && !visit[ny][nx]) {
                    q.push({ny, nx});
                    land[ny][nx] = idx;
                    visit[ny][nx] = true;
                }
            }
        }
    }
    
    return count;
}


int solution(vector<vector<int>> land) {
    
    int area = 2;
    vector<vector<bool>> visit(land.size(), vector<bool>(land[0].size(), false));
    for(int i = 0; i < land.size(); i++) {
        for(int j = 0; j < land[0].size(); j++) {
            if(land[i][j] == 1 && !visit[i][j]) {
                int sz = bfs(land, visit, i, j, area);
                area_sz[area++] = sz;
            }
        }
    }  
    
    int answer = 0;
    for(int i = 0; i < land[0].size(); i++) {
        set<int> used;
        for(int j = 0; j < land.size(); j++) {
            if(land[j][i] != 0) {
                used.insert(land[j][i]);
            }
        }
        
        int now = 0;
        for(auto it = used.begin(); it != used.end(); it++) {
            now += area_sz[*it];
        }
        
        if(answer < now)
            answer = now;
    }
    
    return answer;
}