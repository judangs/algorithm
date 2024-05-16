#include <string>
#include <vector>
#include <iostream>


using namespace std;

vector<vector<int>> change(1003, vector<int>(1003, 0));

int solution(vector<vector<int>> board, vector<vector<int>> skill) {
    for(auto s: skill) {
        int type = s[0];
        if(type == 1) s[5] *= -1;

        // s[type, r1, c1, r2, c2, degree]
        int r1 = s[1];
        int c1 = s[2];
        int r2 = s[3];
        int c2 = s[4];
        int degree = s[5];

        change[r1][c1] += degree;
        change[r2 + 1][c2 + 1] += degree;
        change[r2 + 1][c1] += (degree * -1);
        change[r1][c2 + 1] += (degree * -1);
    }

    for(int i=0; i<board.size(); i++) {
        for(int j=0; j<board.size(); j++) {
            change[i][j + 1] += change[i][j];
        }
    }

    for(int i=0; i<board.size(); i++) {
        for(int j=0; j<board.size(); j++) {
            change[i + 1][j] += change[i][j];
        }
    }


    int answer = 0;
    for(int i=0; i<board.size(); i++) {
        for(int j=0; j<board[0].size(); j++) {
            if(board[i][j] + change[i][j] > 0) answer++;
        }
    }

    return answer;
}