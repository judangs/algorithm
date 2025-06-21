#include <iostream>
#include <vector>
#include <deque>

using namespace std;

int N, K, L;
vector<vector<int>> board;
vector<vector<bool>> visited;

struct Snake {
    int y;
    int x;
    int dir;
};
deque<Snake> dq;

static int dy[] = {-1, 0, 1, 0};
static int dx[] = {0, 1, 0, -1};


bool is_range(int y, int x) {
    return 0 < y && y <= N && 0 < x && x <= N;
}

int main() {

    cin >> N >> K;
    board.resize(N + 1, vector<int>(N + 1, 0));
    visited.resize(N + 1, vector<bool>(N + 1, false));
    
    while(K--) {
        int y, x; cin >> y >> x;
        board[y][x] = 1;
    }

    cin >> L;
    vector<pair<int, char>> query;
    while(L--) {
        int X; char C; cin >> X >> C;
        query.push_back({X, C});
    }

    Snake snake = {1, 1, 1};
    visited[snake.y][snake.x] = true;
    dq.push_front(snake);
    
    int timer = 0, ptr = 0;
    while(true) {

        if(ptr < query.size() && query[ptr].first == timer) {
            char C = query[ptr++].second;
            if(C == 'D') snake.dir = (snake.dir + 1) % 4;
            else snake.dir = (snake.dir + 3) % 4;

        }

        int ny =snake.y + dy[snake.dir], nx = snake.x + dx[snake.dir];
        if(!is_range(ny, nx) || visited[ny][nx]) break;

        snake = {ny, nx, snake.dir};
        dq.push_front(snake);
        visited[ny][nx] = true;

        if(board[ny][nx] == 1) {
            board[ny][nx] = 0;
        }
        else {
            auto tail = dq.back(); dq.pop_back();
            visited[tail.y][tail.x] = false;    
        }
        
        timer++;
    }

    cout << (timer + 1);
}