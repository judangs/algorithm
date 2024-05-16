#include <string>
#include <vector>
#include <queue>
#include <cctype>
#include <iostream>


using namespace std;

vector<vector<string>> make_board;

static int n_y[] = {1, 0, 1};
static int n_x[] = {0, 1, 1};

queue<pair<int, int>> q;


void block_down(int m, int n, vector<string> & board) {
   

    for(int i=m-1; i>0; i--) {
        for(int j=0; j<n; j++) {
            if(board[i][j] == '0') {
                board[i][j] = board[i - 1][j];
                board[i - 1][j] = '0';
            }
        }
    } 
}

bool find_pattern(int m, int n, vector<string> & board) {

    bool flag = false;
    for(int i=0; i<m-1; i++) {
        for(int j=0; j<n-1; j++) {
            if(board[i][j] != '0' && isupper(board[i][j])) {
                int count = 1;
                for(int k=0; k<3; k++) {
                    if(board[i][j] == board[i + n_y[k]][j + n_x[k]]) count++;
                }

                if(count == 4) {
                    q.push({i, j});
                    flag = true;
                }
            }
        }
    }

    return flag;
}

int solution(int m, int n, vector<string> board) {
    while(find_pattern(m, n, board)) {
        while(!q.empty()) {
            int current_y = q.front().first;
            int current_x = q.front().second;
            
            q.pop();
            
            board[current_y][current_x] = '0';
            for(int k=0; k<3; k++) {
                board[current_y + n_y[k]][current_x + n_x[k]] = '0';
            }
        }

        block_down(m, n, board);
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }    
        cout << endl;    
    }

    int answer = 0;
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if(board[i][j] == '0') answer++;
        }
    }

    return answer;
}