#include <iostream>
#include <vector>

using namespace std;

int N, M;
static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

bool is_range(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N >> M;
    vector<vector<char>> board(N, vector<char>(M));
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> board[i][j];
        }
    }

    vector<vector<int>> answer(N, vector<int>(M, 2));
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            for(int dir=0; dir<4; dir++) {
                int ny = i + dy[dir], nx = j + dx[dir];
                if(!is_range(ny, nx)) continue;

                board[ny][nx] = (board[ny][nx] == 'B' ? 'W' : 'B');
            }
        }
    }

    cout << "1\n";
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(board[i][j] == 'B') answer[i][j] = 3;
            cout << answer[i][j];
        }
        cout << "\n";
    }
    
    

}