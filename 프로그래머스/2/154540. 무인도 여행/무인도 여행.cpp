#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

vector<vector<bool>> visit;

static int dx[] = {0, 1, 0, -1};
static int dy[] = {1, 0, -1, 0};

bool check_range(vector<string> maps, int y, int x) {
    return 0 <= y && y <maps.size() && 0 <= x && x < maps[0].size();
}

int bfs(vector<string> & maps, int y, int x) {
    queue<pair<int, int>> q;
    visit[y][x] = true;
    q.push(make_pair(y, x));

    int cost = 0;
    while(!q.empty()) {
        int current_y = q.front().first;
        int current_x = q.front().second;

        q.pop();

        cost += (maps[current_y][current_x] - '0');

        for(int k=0; k<4; k++) {
            int next_y = current_y + dy[k];
            int next_x = current_x + dx[k];
            if(check_range(maps, next_y, next_x) == false) continue;
            if(maps[next_y][next_x] != 'X' && visit[next_y][next_x] == false) {
                visit[next_y][next_x] = true;
                q.push(make_pair(next_y, next_x));
            }
        }
    }
    return cost;
}

vector<int> solution(vector<string> maps) {
    visit.resize(maps.size(), vector<bool>(maps[0].size(), false));

    vector<int> answer;
    for(int i=0; i<maps.size(); i++) {
        for(int j=0; j<maps[i].size(); j++) {
            if(maps[i][j] != 'X' && visit[i][j] == false) {
                int area = bfs(maps, i, j);
                answer.push_back(area);
            }
        }
    }

    sort(answer.begin(), answer.end());
    if(answer.empty())
        return {-1};
    return answer;
}