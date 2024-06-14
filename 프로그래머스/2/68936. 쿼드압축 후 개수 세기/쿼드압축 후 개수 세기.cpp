#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> answer = {0, 0};

void dfs(vector<vector<int>> & arr, int y, int x, int size) {
    
    bool zero = true, one = true;
    for(int i=y; i<y+size; i++) {
        for(int j=x; j<x+size; j++) {
            if(arr[i][j] == 0) one = false;
            if(arr[i][j] == 1) zero = false;
        }
    }

    if(zero == true) {
        answer[0]++;
        return;
    }

    if(one == true) {
        answer[1]++;
        return;
    }

    int next_size = size / 2;

    dfs(arr, y, x, next_size);
    dfs(arr, y, x + next_size, next_size);
    dfs(arr, y + next_size, x, next_size);
    dfs(arr, y + next_size, x + next_size, next_size);
}

vector<int> solution(vector<vector<int>> arr) {
    
    dfs(arr, 0, 0, arr.size());
    return answer;
}