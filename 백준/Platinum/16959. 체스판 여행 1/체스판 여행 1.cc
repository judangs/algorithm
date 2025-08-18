#include <iostream>
#include <memory.h>
#include <queue>

using namespace std;

const int inf = 1e9;
int N;
int sy, sx;
int map[10][10];

static int ndy[8] = {1, 1, 2, 2, -1, -1, -2, -2};
static int ndx[8] = {2, -2, 1, -1, 2, -2, 1, -1};

static int bdy[4] = {1, 1, -1, -1};
static int bdx[4] = {1, -1, 1, -1};

static int ldy[4] = {1, 0, -1, 0};
static int ldx[4] = {0, 1, 0, -1};

struct Node {
    int type, y, x, num;
};
queue<Node> q;

bool check(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int main() {

    cin >> N;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            cin >> map[i][j];
            if(map[i][j] == 1) {
                sy = i, sx = j;
            }
        }


    int visit[3][10][10][101];
    memset(visit, -1, sizeof(visit));

    for(int type=0; type<3; type++) {
        visit[type][sy][sx][1] = 0;
        q.push({type, sy, sx, 1});
    }

    int answer = inf;
    while(!q.empty()) {

        auto node = q.front(); q.pop();
        
        if(node.num == N * N) {
            answer = min(answer, visit[node.type][node.y][node.x][node.num]);
            continue;
        }

        for(int type=0; type<3; type++) {
            if(node.type == type) continue;
            if(visit[type][node.y][node.x][node.num] == -1) {
                visit[type][node.y][node.x][node.num] = visit[node.type][node.y][node.x][node.num] + 1;
                q.push({type, node.y, node.x, node.num});
            }
        }
        
        if(node.type == 0) {
            for(int dir=0; dir<8; dir++) {
                int ny = node.y + ndy[dir], nx = node.x + ndx[dir];
                if(!check(ny, nx)) continue;
                int next = ((node.num + 1) == map[ny][nx] ? (node.num + 1) : node.num);
                if(visit[node.type][ny][nx][next] == -1) {
                    visit[node.type][ny][nx][next] = visit[node.type][node.y][node.x][node.num] + 1;
                    q.push({node.type, ny, nx, next});
                }
            }
        }
        if(node.type == 1) {
            for(int dir=0; dir<4; dir++) {
                for(int step=1; ; step++) {
                    int ny = node.y + bdy[dir] * step, nx = node.x + bdx[dir] * step;
                    if(!check(ny, nx)) break;
                    int next = ((node.num + 1) == map[ny][nx] ? (node.num + 1) : node.num);
                    if(visit[node.type][ny][nx][next] == -1) {
                        visit[node.type][ny][nx][next] = visit[node.type][node.y][node.x][node.num] + 1;
                        q.push({node.type, ny, nx, next});
                    }
                    
                }
            }
        }
        if(node.type == 2) {
            for(int dir=0; dir<4; dir++) {
                for(int step=1; ; step++) {
                    int ny = node.y + ldy[dir] * step, nx = node.x + ldx[dir] * step;
                    if(!check(ny, nx)) break;
                    int next = ((node.num + 1) == map[ny][nx] ? (node.num + 1) : node.num);
                    if(visit[node.type][ny][nx][next] == -1) {
                        visit[node.type][ny][nx][next] = visit[node.type][node.y][node.x][node.num] + 1;
                        q.push({node.type, ny, nx, next});
                    }                    
                }
            }
        }
    }


    cout << answer << endl;
    

}