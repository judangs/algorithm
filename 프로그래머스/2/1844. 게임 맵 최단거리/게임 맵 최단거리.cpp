#include <vector>
#include <queue>
#include <tuple>
#include <iostream>

using namespace std;

static int dx[] = {0, 1, 0, -1};
static int dy[] = {1, 0, -1, 0};

bool check_range(vector<vector<int>> & maps, int y, int x) {
    return 0 <= y && y < maps.size() && 0 <= x && x < maps[0].size();
}

int solution(vector<vector<int>> maps) {
    queue<pair<int, int>> q;
    pair<int, int> dest = make_pair(maps.size() -1, maps[0].size() -1);

    q.push({0, 0});
    
    while(!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        
        q.pop();

        for(int k=0; k<4; k++) {
            int next_y = y + dy[k];
            int next_x = x + dx[k];
            if(check_range(maps, next_y, next_x) == false) continue;
            if(maps[next_y][next_x] == 1) {
                q.push(make_pair(next_y, next_x));
                maps[next_y][next_x] = maps[y][x] + 1;
            }
        }
    }

    if(maps[dest.first][dest.second] == 1)
        return -1;
    else
        return maps[dest.first][dest.second];
}