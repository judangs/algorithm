#include <iostream>
#include <vector>

using namespace std;

int k, dy, dx;
int tile = 1;
vector<vector<int>> board;

bool exist(int sy, int ey, int sx, int ex) {
    
    for(int cy=sy; cy<=ey; cy++) {
        for(int cx=sx; cx<=ex; cx++) {
            if(board[cy][cx] != 0)
                return true;
        }
    }

    return false;
}

void dnC(int sy, int ey, int sx, int ex) {
    
    if(ey - sy == 1 && ex - sx == 1) {
        for(int cy=sy; cy<=ey; cy++) {
            for(int cx=sx; cx<=ex; cx++) {
                if(board[cy][cx] == 0) board[cy][cx] = tile;
            }
        }

        tile++;
        return;
    }

    int my = (sy + ey) / 2, mx = (sx + ex) / 2;
    
    if(!exist(sy, my, sx, mx)) board[my][mx] = tile;
    if(!exist(sy, my, mx + 1, ex)) board[my][mx + 1] = tile;
    if(!exist(my + 1, ey, sx, mx)) board[my + 1][mx] = tile;
    if(!exist(my + 1, ey, mx + 1, ex)) board[my + 1][mx + 1] = tile;

    tile++;

    dnC(sy, my, sx, mx);
    dnC(sy, my, mx + 1, ex);
    dnC(my + 1, ey, sx, mx);
    dnC(my + 1, ey, mx + 1, ex);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> k;
    cin >> dx >> dy;

    int N = 1 << k;
    board.resize(N + 1, vector<int>(N + 1, 0));
    
    board[dy][dx] = -1;
    dnC(1, N, 1, N);

    for(int y=N; y>=1; y--) {
        for(int x=1; x<=N; x++) {
            cout << board[y][x] << " ";
        }
        cout << "\n";
    }

    
}