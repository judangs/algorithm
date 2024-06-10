#include <string>
#include <vector>
#include <iostream>

using namespace std;

static int dy[] = {1, 0, 0, -1};
static int dx[] = {0, -1, 1, 0};
char move_dir[4] = {'d', 'l', 'r', 'u'};

int N, M;
string answer = "";

bool check_range(int y, int x) {
    return 0 < y && y <= N && 0 < x && x <= M;
}

void dfs(int current_y, int current_x, int dest_y, int dest_x, int cost, string pattern) {
    if(cost == 0) {
        if(current_y == dest_y && current_x == dest_x)
            answer = pattern;

        return;
    }

    if(!answer.empty()) return;
    
    int distance = abs(current_y - dest_y) + abs(current_x - dest_x);
    if(distance < cost) {
        if((cost - distance) % 2 != 0)
            return;
    }
    if(distance > cost) return;

    
    for(int k=0; k<4; k++) {
        int next_y = current_y + dy[k];
        int next_x = current_x + dx[k];
        if(check_range(next_y, next_x) == false) continue;
        dfs(next_y, next_x, dest_y, dest_x, cost - 1, pattern + move_dir[k]);
    }
}

string solution(int n, int m, int x, int y, int r, int c, int k) {
    N = n;
    M = m;

    dfs(x, y, r, c, k, "");
    if(answer.empty())
        return "impossible";
    return answer;
}