#include <string>
#include <vector>
#include <iostream>
using namespace std;

struct Position {
    int y;
    int x;

    bool operator==(const Position & o) const { return y == o.y && x == o.x; }
    bool operator!=(const Position & o) const { return !(*this == o); }
};

static inline void move_one(Position & robot, const Position & dest) {
    if (robot.y != dest.y)
        robot.y += (robot.y < dest.y ? 1 : -1);
    else
        robot.x += (robot.x < dest.x ? 1 : -1);
}

static inline int count_conflict(const vector<Position> & robot,
                                 const vector<char> & active) {
    static int cnt[101][101];

    for (int i = 0; i <= 100; i++)
        for (int j = 0; j <= 100; j++)
            cnt[i][j] = 0;

    for (int i = 0; i < (int)robot.size(); i++) {
        if (!active[i]) continue;
        const auto & p = robot[i];
        cnt[p.y][p.x]++;
    }

    int conflict = 0;
    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            if (cnt[i][j] >= 2) conflict++;
        }
    }
    return conflict;
}

int solution(vector<vector<int>> points, vector<vector<int>> routes) {
    int n = (int)routes.size();

    vector<Position> robot(n);
    vector<int> stepIdx(n, 1);
    vector<char> active(n, true);

    for (int i = 0; i < n; i++) {
        int p0 = routes[i][0] - 1;
        robot[i] = { points[p0][0], points[p0][1] };
    }

    int answer = 0;
    answer += count_conflict(robot, active);
    
    for (int i = 0; i < n; i++) {
        if ((int)routes[i].size() == 1) active[i] = false;
    }

    while (true) {
        bool anyMoving = false;

        for (int i = 0; i < n; i++) {
            if (!active[i]) continue;
            if (stepIdx[i] >= (int)routes[i].size()) continue;

            int pid = routes[i][stepIdx[i]] - 1;
            Position target = { points[pid][0], points[pid][1] };

            if (robot[i] != target) {
                anyMoving = true;
                move_one(robot[i], target);
            }
        }

        if (!anyMoving) break;

        answer += count_conflict(robot, active);

        for (int i = 0; i < n; i++) {
            if (!active[i]) continue;
            if (stepIdx[i] >= (int)routes[i].size()) continue;

            int pid = routes[i][stepIdx[i]] - 1;
            Position target = { points[pid][0], points[pid][1] };

            if (robot[i] == target) {
                stepIdx[i]++;

                if (stepIdx[i] >= (int)routes[i].size()) {
                    active[i] = false;
                }
            }
        }
    }

    return answer;
}
