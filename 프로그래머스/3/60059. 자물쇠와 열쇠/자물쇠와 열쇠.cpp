#include <string>
#include <vector>

using namespace std;

vector<vector<int>> board(150, vector<int>(150, 0));

void rotate(vector<vector<int>> & key) {
    
    int m = key.size();
    vector<vector<int>> ret(m, vector<int>(m, 0));
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            ret[j][m - 1 - i] = key[i][j];
        }
    }
    
    key = ret;
}

void fill(vector<vector<int>> & key, int sy, int sx) {
    
    int m = key.size();
    for(int i = sy; i < sy + m; i++) {
        for(int j = sx; j < sx + m; j++) {
            board[i][j] += key[i - sy][j - sx];
        }
    }
}

void fill_out(vector<vector<int>> & key, int sy, int sx) {
    
    int m = key.size();
    for(int i = sy; i < sy + m; i++) {
        for(int j = sx; j < sx + m; j++) {
            board[i][j] -= key[i - sy][j - sx];
        }
    }
}

bool is_valid(int n) {
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(board[50 + i][50 + j] == 2) return false;
            if(board[50 + i][50 + j] == 0) return false;
        }
    }
    
    return true;
}


bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    
    int m = key.size(), n = lock.size();
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            board[50 + i][50 + j] = lock[i][j];
        }
    }
    
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            for(int k = 0; k < 4; k++) {
                rotate(key);
                fill(key, i, j);
                if(is_valid(n))
                    return true;
                fill_out(key, i, j);
            }
        }
    }
    
    return false;
}