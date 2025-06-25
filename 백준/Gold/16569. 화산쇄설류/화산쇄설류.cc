#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>

#define INF 1e9

using namespace std;

int M, N, V;
int X, Y, h, x, y, t;

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

struct Pos {
    int y, x, time;
};
vector<vector<int>> ground;
vector<Pos> volcanos;
vector<vector<bool>> visited;


bool is_range(int cy, int cx) {
    return 0 <= cy && cy < M && 0 <= cx && cx < N;
}


bool is_safe(int cy, int cx, int time) {
    
    if(ground[cy][cx] == -1) return false;
    
    bool safe = true;
    for(auto volcano: volcanos) {
        int distance = abs(cy - volcano.y) + abs(cx - volcano.x);
        if(volcano.time <= time && distance <= (time - volcano.time))
            safe = false;
    }

    return safe;
}


pair<int, int> move(int sy, int sx, int ctime) {

    queue<Pos> q;
    visited[sy][sx] = true;
    q.push({sy, sx, ctime});
    
    int maxh = 0, fast = INF;
    while(!q.empty()) {
        auto now = q.front(); q.pop();

        if(maxh <= ground[now.y][now.x]) {
            if(maxh == ground[now.y][now.x]) fast = min(fast, now.time);
            else {
                maxh = ground[now.y][now.x], fast = now.time;
            }
        }

        for(int dir=0; dir<4; dir++) {
            int ny = now.y + dy[dir], nx = now.x + dx[dir];
            if(!is_range(ny, nx)) continue;
            if(!visited[ny][nx] && is_safe(ny, nx, now.time + 1)) {
                visited[ny][nx] = true;
                q.push({ny, nx, now.time + 1});
            }
        }
    }

    return {maxh, fast};
}

int main() {

    cin >> M >> N >> V;
    cin >> X >> Y;
    
    ground.resize(M, vector<int>(N));
    visited.resize(M, vector<bool>(N, false));

    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
            cin >> ground[i][j];
        }
    }

    for(int i=0; i<V; i++) {
        cin >> x >> y >> t;
        ground[x - 1][y - 1] = -1;
        volcanos.push_back({x - 1, y - 1, t});
    }

    auto answer = move(X - 1, Y - 1, 0);
    cout << answer.first << " " << answer.second;

}