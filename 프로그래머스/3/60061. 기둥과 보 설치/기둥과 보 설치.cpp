#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<vector<bool>>> build;

bool check(int n, int y, int x) {
    return 0 <= y && y <= n && 0 <= x && x <= n;
}

bool valid(int n, int y, int x, int type) {
    if(type == 0) {
        if(y == 0) return true;
        else if(check(n, y-1, x) && build[y-1][x][0] == true) return true;
        else if(check(n, y, x-1) && build[y][x-1][1] == true) return true;
        else if(build[y][x][1] == true) return true;
    }
    else {
        if(check(n, y-1, x) && build[y-1][x][0] == true) return true;
        else if(check(n, y-1, x+1) && build[y-1][x+1][0] == true) return true;
        else if(check(n, y, x-1) && check(n, y, x+1)) {
            if(build[y][x-1][1] == true && build[y][x+1][1] == true) return true;
        }
    }

    return false;
}

bool valid_all(int n) {
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=n; j++) {
            if(build[i][j][0] == true) {
                if(valid(n, i, j, 0) == false) return false;
            }
            if(build[i][j][1] == true) {
                if(valid(n, i, j, 1) == false) return false;
            }
        }
    }

    return true;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    
    build.resize(n + 1, vector<vector<bool>>(n + 1, vector<bool>(2, false)));

    for(auto frame: build_frame) {
        int x = frame[0];
        int y = frame[1];
        int type = frame[2];
        int install = frame[3];

        if(install == 1) {
            if(valid(n, y, x, type) == true) build[y][x][type] = true;
        }
        // 제거
        else {
            build[y][x][type] = false;
            if(valid_all(n) == false) build[y][x][type] = true;
        }
    }

    vector<vector<int>> answer;
    for(int i=0; i<=n; i++) {
        for(int j=0; j<=n; j++) {
            for(int k=0; k<2; k++) {
                if(build[i][j][k] == true) {
                    answer.push_back({j, i, k});
                }
            }
        }
    }

    sort(answer.begin(), answer.end());
    return answer;
}