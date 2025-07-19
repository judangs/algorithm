#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1e9

using namespace std;

int n, m;
struct Position {
    int y, x;
};

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

vector<vector<int>> board;
vector<int> food(6, -1);

bool check(Position where) {
    return 0 <= where.y && where.y < n && 0 <= where.x && where.x < m;
}

void bfs(Position start) {
    queue<pair<Position, int>> q;
    vector<vector<bool>> visit(n, vector<bool>(m, false));

    q.push({start, 0});
    visit[start.y][start.x] = true;

    while(!q.empty()) {
        Position now = q.front().first; int cost = q.front().second;
        q.pop();

        for(int dir=0; dir<4; dir++) {
            Position next = Position{now.y + dy[dir], now.x + dx[dir]};
            if(!check(next)) continue;
            if(!visit[next.y][next.x]) {
                int & type = board[next.y][next.x];
                if(type != 1) {
                    if(type > 2) food[type] = cost + 1;
                    visit[next.y][next.x] = true;
                    q.push({next, cost + 1});
                }
            }
        }        
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    board.resize(n, vector<int>(m));
    
    int sy, sx;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            char type; cin >> type;
            board[i][j] = type - '0';
            if(board[i][j] == 2) {
                sy = i, sx = j;
            }
        }
    }

    bfs({sy, sx});
    int distance = INF;
    for(int type=3; type<=5; type++) {
        if(food[type] != -1) distance = min(distance, food[type]);
    }

    if(distance == INF) cout << "NIE" << endl;
    else {
        cout << "TAK" << endl;
        cout << distance << endl;
    }

}