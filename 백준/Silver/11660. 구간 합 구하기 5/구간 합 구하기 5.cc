#include <iostream>
#include <vector>

using namespace std;

int N, M;
vector<vector<int>> board;
vector<vector<long long>> prefix;

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    board.resize(N, vector<int>(N));
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> board[i][j];
        }
    }

    prefix.resize(N + 1, vector<long long>(N + 1, 0));
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + board[i - 1][j - 1];
        }
    }


    int sx, sy, ex, ey;
    for(int i=0; i<M; i++) {
        cin >> sy >> sx >> ey >> ex;
        cout << prefix[ey][ex] - prefix[ey][sx - 1] - prefix[sy - 1][ex] + prefix[sy - 1][sx - 1] << "\n";
    }
}