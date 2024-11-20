#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int answer = INT32_MAX;

void turn_col(vector<vector<int>> & beginning, int x) {
    for(int row=0; row<beginning.size(); row++) {
        beginning[row][x] ^= 1;
    }
}

void turn_row(vector<vector<int>> & beginning, int row) {
    for(int col=0; col<beginning[0].size(); col++) {
        beginning[row][col] ^= 1;
    }
}

void check(vector<vector<int>> beginning, vector<vector<int>> & target, int count) {
    
    int ret = 0;
    for(int row=0; row<target.size(); row++) {
        bool flag = false;
        for(int col=0; col<target[0].size(); col++) {
            if(beginning[row][col] != target[row][col]) {
                flag = true;
                break;
            }
        }
        
        if(flag) {
            turn_row(beginning, row);
            ret += 1;
        }
    }
    
    
    for(int row=0; row<target.size(); row++) {
        for(int col=0; col<target[0].size(); col++) {
            if(beginning[row][col] != target[row][col]) {
                return;
            }
        }
    }
    
    answer = min(answer, ret + count);
}

void dfs(vector<vector<int>> beginning, vector<vector<int>> & target, int x, int count) {
    
    if(x == beginning[0].size()) {
        check(beginning, target, count);
        return;
    }
    
    dfs(beginning, target, x + 1, count);
    turn_col(beginning, x);
    dfs(beginning, target, x + 1, count + 1);

}


int solution(vector<vector<int>> beginning, vector<vector<int>> target) {
    
    dfs(beginning, target, 0, 0);
    return (answer != INT32_MAX ? answer : -1);
    
    
}