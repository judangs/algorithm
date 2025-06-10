#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Position {
    int y;
    int x;

    bool operator!=(const Position & o) const {
        return (y != o.y || x != o.x);
    }
};

struct Edge {
    int start;
    int end;
    int cost;
};

int N, M;
vector<vector<char>> board;
vector<Position> robot;
vector<Edge> edges;

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool is_range(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

void bfs(Position start) {
    queue<pair<Position, int>> q;
    vector<vector<bool>> visit(N, vector<bool>(N, false));

    q.push({start, 0});
    visit[start.y][start.x] = true;

    while(!q.empty()) {

        auto current = q.front().first;
        int cost = q.front().second;

        q.pop();

        if(current != start) {
            if(board[current.y][current.x] == 'K' || board[current.y][current.x] == 'S') {
                edges.push_back({N * start.y + start.x, N * current.y + current.x, cost});
            }
        }

        for(int dir=0; dir<4; dir++) {
            int ny = current.y + dy[dir], nx = current.x + dx[dir];
            if(!is_range(ny, nx)) continue;

            if(board[ny][nx] != '1' && !visit[ny][nx]) {
                visit[ny][nx] = true;
                q.push({{ny, nx}, cost + 1});
            }
        }
    }
}

int find(int node, vector<int> & parent) {
    if(parent[node] == node) return node;
    return (parent[node] = find(parent[node], parent));
}

int main() {
    
    cin >> N >> M;

    board.resize(N, vector<char>(N));

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> board[i][j];
            if(board[i][j] == 'S' || board[i][j] == 'K')
                robot.push_back({ i, j });
        }
    }

    for(auto pos: robot) bfs(pos);

    vector<int> parent(N * N + N);
    for(int node=0; node<parent.size(); node++) 
        parent[node] = node;


    sort(edges.begin(), edges.end(), [](const Edge & l, const Edge & r) {
        return l.cost < r.cost;
    });

    int answer = 0;
    for(auto e: edges) {
        int ps = find(e.start, parent), pe = find(e.end, parent);
        if(ps != pe) {
            if(ps < pe) parent[pe] = ps;
            else parent[ps] = pe;

            answer += e.cost;
        }
    }

    int group = find(N * robot.front().y + robot.front().x, parent);
    for(int idx=1; idx<robot.size(); idx++) {
        int cg = find(N * robot[idx].y + robot[idx].x, parent);
        if(group != cg) {
            cout << "-1";
            exit(0);
        }
    }

    cout << answer;
}