#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int N, M;
int board[500][500], up[500][500];
int front[500], aside[500];

void invalid() {
    cout << "-1" << endl;
    exit(0);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++) cin >> up[i][j];

    for(int i=0; i<M; i++) cin >> front[i];
    for(int i=N-1; i>=0; i--) cin >> aside[i];

    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            if(up[i][j]) board[i][j] = min(front[j], aside[i]);

    for(int i=0, h = 0; i<N; i++, h = 0) {
        for(int j=0; j<M; j++) {
            if(up[i][j] && !board[i][j]) invalid();
            h = max(h, board[i][j]);
        }

        if(h != aside[i]) invalid();
    }
    for(int i=0, h=0; i<M; i++, h = 0) {
        for(int j=0; j<N; j++) {
            h = max(h, board[j][i]);
        }

        if(h != front[i]) invalid();
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

}