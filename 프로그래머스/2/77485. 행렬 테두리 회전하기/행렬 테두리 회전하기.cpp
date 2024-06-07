#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> board;

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    board.resize(rows + 1, vector<int>(columns + 1, 0));
    
    int current = 1;
    for(int row=1; row<=rows; row++) {
        for(int column=1; column<=columns; column++) {
            board[row][column] = current++;
        }
    }
    
    vector<int> answer;
    for(vector<int> query: queries) {
        int s_y = query[0];
        int s_x = query[1];
        int e_y = query[2];
        int e_x = query[3];

        int tmp = board[s_y][s_x];
        int answer_tmp = tmp;
        for(int right=s_x + 1; right<=e_x; right++) {
            int next_tmp = board[s_y][right];
            board[s_y][right] = tmp;
            tmp = next_tmp;
            answer_tmp = min(answer_tmp, tmp);
        }

        for(int down=s_y+1; down<=e_y; down++) {
            int next_tmp = board[down][e_x];
            board[down][e_x] = tmp;
            tmp = next_tmp;
            answer_tmp = min(answer_tmp, tmp);
        }

        
        for(int left=e_x-1; left>=s_x; left--) {
            int next_tmp = board[e_y][left];
            board[e_y][left] = tmp;
            tmp = next_tmp;
            answer_tmp = min(answer_tmp, tmp);
        }

        for(int up=e_y-1; up>=s_y; up--) {
            int next_tmp = board[up][s_x];
            board[up][s_x] = tmp;
            tmp = next_tmp;
            answer_tmp = min(answer_tmp, tmp);
        }

        answer.push_back(answer_tmp);
    }

    return answer;
}