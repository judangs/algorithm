#include <iostream>
#include <vector>

using namespace std;

int N, M;

int main() {
    cin >> N >> M;

    vector<vector<int>> board(N, vector<int>(M));
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> board[i][j];
        }
    }

    vector<vector<int>> flow(N, vector<int>(M)), reverse(N, vector<int>(M));
    for(int i=1; i<M; i++) {
        board[0][i] += board[0][i - 1];
    }

    for(int i=1; i<N; i++) {

        flow[i][0] = board[i - 1][0] + board[i][0];
        reverse[i][M - 1] = board[i - 1][M - 1] + board[i][M - 1];
        for(int j=1; j<M; j++) {
            flow[i][j] = max(flow[i][j - 1], board[i - 1][j]) + board[i][j];
            reverse[i][M - 1 - j] = max(reverse[i][M - j], board[i - 1][M - 1 - j]) + board[i][M - 1 - j];
        }

        for(int j=0; j<M; j++) {
            board[i][j] = max(flow[i][j], reverse[i][j]);
        }
    }

    cout << board[N - 1][M - 1];
}