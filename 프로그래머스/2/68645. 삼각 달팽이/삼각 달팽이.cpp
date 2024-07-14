#include <string>
#include <vector>

using namespace std;

vector<vector<int>> board;

int c_y = -1;
int c_x = 0;

static int dy[] = {1, 0, -1};
static int dx[] = {0, 1, -1};

int draw_board(int count, int dir, int current) {
    for(int i=count; i>0; i--) {
        c_y += dy[dir % 3];
        c_x += dx[dir % 3];
        
        board[c_y][c_x] = current++;
    }
    
    return current;
}

vector<int> solution(int n) {
    
    board.resize(n, vector<int>(n));
    
    int count = n, dir = 0;
    int current = 1;
    while(count > 0) {
        int next = draw_board(count, dir, current);
        current = next;
        count--;
        dir++;
    }
    
    vector<int> answer;
    for(int i=0; i<n; i++) {
        for(int j=0; j<=i; j++) {
            answer.push_back(board[i][j]);
        }
    }
    
    return answer;
}