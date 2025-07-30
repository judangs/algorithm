#include <iostream>
#include <vector>

using namespace std;

int k, dy, dx;
int tile = 1;
vector<vector<int>> board;

bool exist(int y, int x, int size) {
    for(int cy=y; cy<y+size; cy++) {
        for(int cx=x; cx<x+size; cx++) {
            if(board[cy][cx] != 0)
                return true;
        }
    }

    return false;
}

void dnC(int y, int x, int size) {
    
    if(size == 2) {
        for(int cy=y; cy<y+size; cy++) {
            for(int cx=x; cx<x+size; cx++) {
                if(board[cy][cx] == 0)
                    board[cy][cx] = tile;
            }
        }

        tile++;
        return;
    }

    size >>= 1;
    int ey = y + size - 1, ex = x + size - 1;

    if(!exist(y, x, size)) board[ey][ex] = tile;
    if(!exist(y, ex + 1, size)) board[ey][ex + 1] = tile;
    if(!exist(ey + 1, x, size)) board[ey + 1][ex] = tile;
    if(!exist(ey + 1, ex + 1, size)) board[ey + 1][ex + 1] = tile;

    tile++;

    dnC(y, x, size);
    dnC(y, ex + 1, size);
    dnC(ey + 1, x, size);
    dnC(ey + 1, ex + 1, size);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> k;
    cin >> dx >> dy;


    int N = 1 << k;
    board.resize(N + 1, vector<int>(N + 1, 0));

    board[dy][dx] = -1;
    dnC(1, 1, N);

    for(int y=N; y>=1; y--) {
        for(int x=1; x<=N; x++) {
            cout << board[y][x] << " ";
        }
        cout << "\n";
    }

    
}