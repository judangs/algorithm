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

struct Cell {
    int time, change;
    
    bool operator<(const Cell & o) const {
        if(time == o.time)
            return change < o.change;
        return time < o.time;
    }

    bool operator==(const Cell & o) const {
        return time == o.time && change == o.change;
    }

    Cell move() {
        return Cell{time + 1, change};
    }

    Cell swap() {
        return Cell{time + 1, change + 1};
    }
};

struct Node {
    int type, y, x, num;
    Cell cell;

    bool operator>(const Node & o) const {
        if(cell.time == o.cell.time)
            return cell.change > o.cell.change;
        return cell.time > o.cell.time;
    }
};
priority_queue<Node, vector<Node>, greater<Node>> pq;


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


    Cell visit[3][10][10][101];
    for(int type=0; type<3; type++) for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
        for(int num = 0; num < N * N + 1; num++)
            visit[type][i][j][num] = Cell{inf, inf};

    for(int type=0; type<3; type++) {
        visit[type][sy][sx][1] = {0, 0};
        pq.push({type, sy, sx, 1, visit[type][sy][sx][1]});
    }

    Cell answer = Cell{inf, inf};
    while(!pq.empty()) {

        auto node = pq.top(); pq.pop();
        
        if(node.num == N * N) {
            if(node.cell < answer) answer = node.cell;
            continue;
        }

        for(int type=0; type<3; type++) {
            if(node.type == type) continue;
            if(visit[node.type][node.y][node.x][node.num].swap() < visit[type][node.y][node.x][node.num]) {
                visit[type][node.y][node.x][node.num] = visit[node.type][node.y][node.x][node.num].swap();
                pq.push({type, node.y, node.x, node.num, visit[type][node.y][node.x][node.num]});
            }
        }
        
        if(node.type == 0) {
            for(int dir=0; dir<8; dir++) {
                int ny = node.y + ndy[dir], nx = node.x + ndx[dir];
                if(!check(ny, nx)) continue;
                int next = ((node.num + 1) == map[ny][nx] ? (node.num + 1) : node.num);
                if(visit[node.type][node.y][node.x][node.num].move() < visit[node.type][ny][nx][next]) {
                    visit[node.type][ny][nx][next] = visit[node.type][node.y][node.x][node.num].move();
                    pq.push({node.type, ny, nx, next, visit[node.type][ny][nx][next]});
                }
            }
        }
        if(node.type == 1) {
            for(int dir=0; dir<4; dir++) {
                for(int step=1; ; step++) {
                    int ny = node.y + bdy[dir] * step, nx = node.x + bdx[dir] * step;
                    if(!check(ny, nx)) break;
                    int next = ((node.num + 1) == map[ny][nx] ? (node.num + 1) : node.num);
                    if(visit[node.type][node.y][node.x][node.num].move() < visit[node.type][ny][nx][next]) {
                        visit[node.type][ny][nx][next] = visit[node.type][node.y][node.x][node.num].move();
                        pq.push({node.type, ny, nx, next, visit[node.type][ny][nx][next]});
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
                    if(visit[node.type][node.y][node.x][node.num].move() < visit[node.type][ny][nx][next]) {
                        visit[node.type][ny][nx][next] = visit[node.type][node.y][node.x][node.num].move();
                        pq.push({node.type, ny, nx, next, visit[node.type][ny][nx][next]});
                    }                    
                }
            }
        }
    }


    cout << answer.time<< " " << answer.change << endl;
    

}