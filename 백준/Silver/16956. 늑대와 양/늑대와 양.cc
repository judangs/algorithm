#include <iostream>
#include <vector>

using namespace std;

int R, C;

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool check(int y, int x) {
    return 0 <= y && y < R && 0 <= x && x < C;
}

int main() {
    
    cin >> R >> C;
    vector<vector<char>> board(R, vector<char>(C));
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++) cin >> board[i][j];


    bool obstruct = true;
    for(int i=0; i<R; i++)
        for(int j=0; j<C; j++) {
            for(int dir=0; dir<4; dir++) {
                int ny = i + dy[dir], nx = j + dx[dir];
                if(!check(ny, nx)) continue;
                if(board[i][j] == 'S') {
                    if(board[ny][nx] == 'W') obstruct = false;
                    if(board[ny][nx] == '.') board[ny][nx] = 'D';
                }
            }
        }

    if(obstruct) {
        cout << "1\n";
        for(int i=0; i<R; i++) {
            for(int j=0; j<C; j++) {
                cout << board[i][j];
            }            
            cout << "\n";
        }
    }
    else {
        cout << "0";
    }
    
    
}