#include <iostream>
#include <vector>

using namespace std;

int N, M, r, c, d;

static int dy[] = {-1, 0, 1, 0};
static int dx[] = {0, 1, 0, -1};

struct Cleaner {
    int y;
    int x;
    int dir;  
};

int room[51][51];
int visited[51][51];

bool is_range(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}

int main() {

    cin >> N >> M;
    cin >> r >> c >> d;
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++) cin >> room[i][j];

    Cleaner robot = {r, c, d};
    while(true) {

        visited[robot.y][robot.x] = true;
        
        bool find = false;
        for(int dir=0; dir<4; dir++) {
            int ny = robot.y + dy[dir], nx = robot.x + dx[dir];
            if(!is_range(ny, nx)) continue;
            if(room[ny][nx] == 0 && !visited[ny][nx]) find = true;
        }

        if(!find) {
            int back = (robot.dir + 2) % 4;
            int ny = robot.y + dy[back], nx = robot.x + dx[back];
            if(!is_range(ny, nx) || room[ny][nx] == 1) break;
            robot = {ny, nx, robot.dir};
        }
        else {
            robot.dir = (robot.dir + 3) % 4;
            int ny = robot.y + dy[robot.dir], nx = robot.x + dx[robot.dir];
            if(!visited[ny][nx] && room[ny][nx] == 0) {
                robot = {ny, nx, robot.dir};
            }
        }
    }

    int answer = 0;
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            if(visited[i][j]) answer++;
    
    cout << answer;

}