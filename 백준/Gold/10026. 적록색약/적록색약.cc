#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
char board[101][101];

struct Pos {
    int y, x;
};

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool check(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int bfs(int y, int x, bool blind, vector<vector<bool>> & visit) {

    queue<Pos> q;
    q.push({y, x});
    visit[y][x] = true;

    while(!q.empty()) {
        auto now = q.front(); q.pop();
        char & current = board[now.y][now.x];
        
        for(int dir=0; dir<4; dir++) {
            int ny = now.y + dy[dir], nx = now.x + dx[dir];
            if(!check(ny, nx)) continue;

            char & next = board[ny][nx];
            
            if(current == 'R' || current == 'G') {
                if(blind && (next == 'R' || next == 'G')) {
                    if(!visit[ny][nx]) {
                        visit[ny][nx] = true;
                        q.push({ny, nx});
                    }
                }
                else {
                    if(current == next) {
                        if(!visit[ny][nx]) {
                            visit[ny][nx] = true;
                            q.push({ny, nx});
                        }
                    }
                }
            }
            else {
                if(current == next) {
                    if(!visit[ny][nx]) {
                        visit[ny][nx] = true;
                        q.push({ny, nx});
                    }
                }
            }
        }
    }

    return 1;

}

int area(bool blind) {
    
    vector<vector<bool>> visit(N, vector<bool>(N, false));

    int answer = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(!visit[i][j])
                answer += bfs(i, j, blind, visit);
        }
    }

    return answer;
}

int main() {

    cin >> N;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            char color; cin >> color;
            board[i][j] = color;
        }
    }

    cout << area(false) << " " << area(true) << endl;
    

}