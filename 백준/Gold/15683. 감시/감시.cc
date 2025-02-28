#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> board;
vector<vector<int>> visited;
vector<pair<int, int>> cctv;

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

int answer = 1e9;

bool check_range(int y, int x) {
    return 0 <= y && y < board.size() &&  0 <= x && x < board[0].size();
}

void fill_board(pair<int, int> pos, int dir) {
    queue<pair<int, int>> q; 
    if(check_range(pos.first + dy[dir], pos.second + dx[dir])) {
        q.push({pos.first + dy[dir], pos.second + dx[dir]});
    }
    while(!q.empty()) {
        
        auto current = q.front();
        q.pop();

        if(board[current.first][current.second] == 6) return;
        else {
            if(board[current.first][current.second] == 0 || board[current.first][current.second] == -1) {
                board[current.first][current.second] = -1;
                visited[current.first][current.second]++;                
            }
            pair<int, int> next = {current.first + dy[dir], current.second + dx[dir]};    

            if(check_range(next.first, next.second)) {
                q.push(next);
            }
        }
    }  
}


void remove_board(pair<int, int> pos, int dir) {
    queue<pair<int, int>> q; 
    if(check_range(pos.first + dy[dir], pos.second + dx[dir])) {
        q.push({pos.first + dy[dir], pos.second + dx[dir]});
    }
    while(!q.empty()) {
        
        auto current = q.front();
        q.pop();

        if(board[current.first][current.second] == 6) return;
        else {
            if(board[current.first][current.second] == -1) {
                visited[current.first][current.second]--;
                if(visited[current.first][current.second] == 0) {
                    board[current.first][current.second] = 0;                    
                }
            }
            pair<int, int> next = {current.first + dy[dir], current.second + dx[dir]};    

            if(check_range(next.first, next.second)) {
                q.push(next);
            }
        }
    }      
}


void dfs(int depth) {
    if(depth == cctv.size()) {

        int count = 0;
        for(int i=0; i<N; i++) {
            for(int j=0; j<M; j++) {
                if(board[i][j] == 0) {
                    count++;
                }
            }
        }

        answer = min(answer, count);
        return;
    }

    auto c = cctv[depth];


    for(int dir=0; dir<4; dir++) {
        if(board[c.first][c.second] == 1) {
            fill_board(c, dir);
            dfs(depth + 1);
            remove_board(c, dir);
        }
        else if(board[c.first][c.second] == 2) {
            fill_board(c, dir);
            fill_board(c, (dir + 2) % 4);
            dfs(depth + 1);
            remove_board(c, dir);
            remove_board(c, (dir + 2) % 4);
        }
        else if(board[c.first][c.second] == 3) {
            fill_board(c, dir);
            fill_board(c, (dir + 1) % 4);
            dfs(depth + 1);
            remove_board(c, dir);
            remove_board(c, (dir + 1) % 4);
        }
        else if(board[c.first][c.second] == 4) {
            fill_board(c, dir);
            fill_board(c, (dir + 1) % 4);
            fill_board(c, (dir + 2) % 4);
            dfs(depth + 1);
            remove_board(c, dir);
            remove_board(c, (dir + 1) % 4); 
            remove_board(c, (dir + 2) % 4);                
        }
        else {
            fill_board(c, dir);
            fill_board(c, (dir + 1) % 4);
            fill_board(c, (dir + 2) % 4);
            fill_board(c, (dir + 3) % 4);
            dfs(depth + 1);
            remove_board(c, dir);
            remove_board(c, (dir + 1) % 4); 
            remove_board(c, (dir + 2) % 4);
            remove_board(c, (dir + 3) % 4);   
        }
    }
}

int main() {
    cin >> N >> M;
    
    board.resize(N, vector<int>(M));
    visited.resize(N, vector<int>(M, 0));
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> board[i][j];
            if(board[i][j] != 0 && board[i][j] != 6) {
                cctv.push_back({i, j});
            }
        }
    }


    dfs(0);
    cout << answer;
}