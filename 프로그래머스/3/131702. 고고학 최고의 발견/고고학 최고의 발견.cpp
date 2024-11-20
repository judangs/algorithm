#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int dy[] = {0, 1, 0, -1, 0};
int dx[] = {0, 0, 1, 0, -1};

bool check_range(int n, int y, int x) {
    return 0 <= y && y < n && 0 <= x && x < n;
}

void rotate(vector<vector<int>> & clocks, int y, int x, int turn, int flag) {
    
    for(int k=0; k<5; k++) {
        int ny = y + dy[k];
        int nx = x + dx[k];
        if(check_range(clocks.size(), ny, nx) == false) continue;
        if(flag == true) {
            clocks[ny][nx] += turn;
            clocks[ny][nx] %= 4;
        }
        else {
            clocks[ny][nx] = (clocks[ny][nx] - turn + 4) % 4;
        }
    }
    
}

int answer = INT32_MAX;

void down(vector<vector<int>> clocks, int count) {
    
    int ret = 0;
    for(int row=1; row<clocks.size(); row++) {
        for(int col=0; col<clocks.size(); col++) {
            int r = (4 - clocks[row - 1][col]) % 4;
            rotate(clocks, row, col, r, true);
            
            ret += r;
        }
    }
    
    int flag = true;
    for(int row=0; row<clocks.size(); row++) {
        for(int col=0; col<clocks.size(); col++) {
            if(clocks[row][col] != 0)
                flag = false;
        }
    }
    
    if(flag) {
        answer = min(answer, ret + count);
    }
}


void dfs(vector<vector<int>> & clocks, int x, int count) {
    
    if(x == clocks.size()) {
        down(clocks, count);
        return;
    }
    
    for(int turn=0; turn<4; turn++) {
        rotate(clocks, 0, x, turn, true);
        dfs(clocks, x + 1, count + turn);
        rotate(clocks, 0, x, turn, false);
    }
    
}

int solution(vector<vector<int>> clockHands) {
    
    dfs(clockHands, 0, 0);
    return answer;
    
}