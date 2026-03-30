#include <string>
#include <vector>

using namespace std;

bool is_finish(const vector<string>& board, char c) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c) return true;
        if (board[0][i] == c && board[1][i] == c && board[2][i] == c) return true;
    }
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return true;
    if (board[0][2] == c && board[1][1] == c && board[2][0] == c) return true;
    return false;
}

bool dfs(vector<string>& board) {
    int o = 0, x = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'O') o++;
            else if (board[i][j] == 'X') x++;
        }
    }

    // 빈 보드면 시작 상태
    if (o == 0 && x == 0) return true;

    // 개수 규칙 위반
    if (x > o || o > x + 1) return false;

    bool oWin = is_finish(board, 'O');
    bool xWin = is_finish(board, 'X');

    // 둘 다 이긴 상태는 불가능
    if (oWin && xWin) return false;

    // 이번 단계에서 지워야 할 "마지막 수"의 말
    char last;
    if (o == x + 1) last = 'O';
    else if (o == x) last = 'X';
    else return false;

    // 승자가 있다면 마지막 수를 둔 사람이 승자여야 함
    if (oWin && last != 'O') return false;
    if (xWin && last != 'X') return false;

    // last 말을 하나 지워 보면서 직전 상태가 가능한지 확인
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != last) continue;

            board[i][j] = '.';

            // 마지막 수를 지운 뒤에는, 직전 상태에서 상대가 이미 이기고 있으면 안 됨
            // 이미 끝난 게임 뒤에 더 둔 셈이 되기 때문
            char prev = (last == 'O' ? 'X' : 'O');
            bool valid = !is_finish(board, prev) && dfs(board);

            board[i][j] = last;

            if (valid) return true;
        }
    }

    return false;
}

int solution(vector<string> board) {
    return dfs(board) ? 1 : 0;
}