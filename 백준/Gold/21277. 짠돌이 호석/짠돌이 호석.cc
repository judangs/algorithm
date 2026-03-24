#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N, M;
vector<string> puzzle[2];


void fill(vector<vector<char>> & board, vector<string> puzzle, int sy, int sx) {

    for(int i = sy; i < sy + puzzle.size(); i++) {
        for(int j = sx; j < sx + puzzle.front().size(); j++) {
            if(puzzle[i - sy][j - sx] == '1') {
                board[i][j] += 1;
            }
        }
    }
}

int area(vector<vector<char>> & board) {

    int sy = inf, sx = inf, ey = 0, ex = 0;
    for(int i = 0; i < board.size(); i++) {
        for(int j = 0; j < board[0].size(); j++) {
            if('1' == board[i][j]) {
                sy = min(sy, i), sx = min(sx, j), ey = max(ey, i), ex = max(ex, j);
            }
            if('2' == board[i][j])
                return inf;
        }
    }

    return ((ey - sy + 1) * (ex - sx + 1));

}

void fill_out(vector<vector<char>> & board, vector<string> puzzle, int sy, int sx) {

    for(int i = sy; i < sy + puzzle.size(); i++) {
        for(int j = sx; j < sx + puzzle.front().size(); j++) {
            if(puzzle[i - sy][j - sx] == '1') {
                board[i][j] -= 1;
            }
        }
    }    

}

void rotate(vector<string> & puzzle) {

    int n = puzzle.size();
    int m = puzzle[0].size();

    vector<string> temp(m, string(n, '0'));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            temp[j][n - 1 - i] = puzzle[i][j];
        }
    }

    puzzle = temp;

}

int main() {

    cin >> N >> M;
    puzzle[0] = vector<string> (N);
    for(auto & cell: puzzle[0]) cin >> cell;

    cin >> N >> M;
    puzzle[1] = vector<string> (N);
    for(auto & cell: puzzle[1]) cin >> cell;

    int n1 = puzzle[0].size(), m1 = puzzle[0][0].size(), n2 = puzzle[1].size(), m2 = puzzle[1][0].size();
    vector<vector<char>> board(150, vector<char>(150, '0'));

    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m1; j++) {
            board[50 + i][50 + j] = puzzle[0][i][j];
        }
    }    

    int ans = inf;
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            for(int k = 0; k < 4; k++) {
                rotate(puzzle[1]);
                fill(board, puzzle[1], i, j);
                ans = min(ans, area(board));
                fill_out(board, puzzle[1], i, j);
            }
        }
    }


    cout << ans << '\n';


}