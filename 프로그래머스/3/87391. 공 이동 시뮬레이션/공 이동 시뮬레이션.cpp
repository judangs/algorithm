#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Pos {
    long long y;
    long long x;
};

bool check(int n, int m, Pos pos) {
    return 0 <= pos.y && pos.y < n && 0 <= pos.x && pos.x < m;
}

long long solution(int n, int m, int x, int y, vector<vector<int>> queries) {
    reverse(queries.begin(), queries.end());

    Pos start = {x, y};
    Pos end = {x, y};

    for(auto query: queries) {
        int type = query[0];
        int dx = query[1];

        switch(type) {

            // 열 감소.
            case 0:
                if(start.x == 0) {
                    end.x += dx;
                }
                else {
                    start.x += dx;
                    end.x += dx;
                }
                if(end.x >= m) end.x = m - 1;
                if(start.x >= m) return 0;
                break;

            // 열 증가.
            case 1:
                if(end.x == m - 1) {
                    start.x -= dx;
                }
                else {
                    start.x -= dx;
                    end.x -= dx;
                }
                if(start.x < 0) start.x = 0;
                if(start.x < 0) return 0;
                break;
            
            // 행 감소
            case 2:
                if(start.y == 0) {
                    end.y += dx;
                }
                else {
                    start.y += dx;
                    end.y += dx;
                }
                if(end.y >= n) end.y = n - 1;
                if(start.y >= n) return 0;
                break;
            // 행 증가
            case 3:
                if(end.y == n - 1) {
                    start.y -= dx;
                }
                else {
                    start.y -= dx;
                    end.y -= dx;
                }
                if(start.y < 0) start.y = 0;
                if(end.y < 0) return 0;
                break;
        }
    }

    long long answer = 0;
    if(check(n, m, start) && check(n, m, end)) {
        answer = (end.y - start.y + 1) * (end.x - start.x + 1);
        return answer;
    }
    else
        return answer;
}