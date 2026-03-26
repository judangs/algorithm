#include <vector>
#include <algorithm>
#include <bitset>
#include <cmath>

using namespace std;

const int MAXV = 100;

int n, totalLocker, needPeople, bestClique;
vector<pair<int, int>> pos;
int distTable[MAXV][MAXV];
bitset<MAXV> adjByDist[20][MAXV];

void colorSort(const vector<int>& cand, vector<int>& order, vector<int>& bound, int d) {
    vector<int> cur = cand;
    order.clear();
    bound.clear();

    int color = 0;
    while (!cur.empty()) {
        color++;
        vector<int> next;
        bitset<MAXV> used;

        // greedy coloring으로 clique 상한을 계산해서
        // 이후 DFS에서 "여기서 최대 몇 명까지 더 뽑을 수 있는지"를 빠르게 가지치기한다.
        for (int v : cur) {
            if ((used & adjByDist[d][v]).any()) next.push_back(v);
            else {
                used.set(v);
                order.push_back(v);
                bound.push_back(color);
            }
        }
        cur.swap(next);
    }
}

void maxClique(vector<int>& cand, int cnt, int d) {
    if (cand.empty()) {
        if (cnt > bestClique) bestClique = cnt;
        return;
    }

    vector<int> order, bound;
    colorSort(cand, order, bound, d);

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        // greedy coloring으로 얻은 상한(bound)으로
        // 현재 cnt에서 더 가도 bestClique를 못 넘으면 즉시 종료한다.
        if (cnt + bound[i] <= bestClique) return;

        int v = order[i];
        vector<int> next;
        next.reserve(i);

        // 후보 전체를 다시 보지 않고,
        // 현재 정점 v와 연결된 후보만 남겨서 다음 단계로 내려간다.
        for (int j = 0; j < i; j++) {
            int u = order[j];
            if (adjByDist[d][v].test(u)) next.push_back(u);
        }

        if (cnt + 1 > bestClique) bestClique = cnt + 1;
        if (!next.empty()) maxClique(next, cnt + 1, d);
    }
}

bool canPlace(int d) {
    if (needPeople <= 1) return true;
    if (d <= 1) return true;

    if (d == 2) {
        int black = 0, white = 0;
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < n; x++) {
                if ((y + x) % 2 == 0) black++;
                else white++;
            }
        }
        return max(black, white) >= needPeople;
    }

    vector<int> cand(totalLocker);
    for (int i = 0; i < totalLocker; i++) cand[i] = i;

    // 차수가 큰 정점부터 시작하면 초반에 큰 clique를 빨리 찾기 쉬워져서
    // bestClique가 빨리 커지고 이후 가지치기가 더 강해진다.
    sort(cand.begin(), cand.end(), [d](int a, int b) {
        return (int)adjByDist[d][a].count() > (int)adjByDist[d][b].count();
    });

    bestClique = 0;
    maxClique(cand, 0, d);

    return bestClique >= needPeople;
}

int solution(int nInput, int m, vector<vector<int>> timetable) {
    n = nInput;
    totalLocker = n * n;

    vector<pair<int, int>> events;
    for (auto& t : timetable) {
        events.push_back({t[0], +1});
        events.push_back({t[1], -1});
    }

    sort(events.begin(), events.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });

    int cur = 0;
    needPeople = 0;
    for (auto& e : events) {
        cur += e.second;
        needPeople = max(needPeople, cur);
    }

    if (needPeople <= 1) return 0;

    pos.clear();
    for (int y = 0; y < n; y++) {
        for (int x = 0; x < n; x++) {
            pos.push_back({y, x});
        }
    }

    for (int i = 0; i < totalLocker; i++) {
        for (int j = 0; j < totalLocker; j++) {
            distTable[i][j] = abs(pos[i].first - pos[j].first)
                            + abs(pos[i].second - pos[j].second);
        }
    }

    int maxDist = 2 * (n - 1);

    // 거리별 그래프를 미리 전부 만들어 두면
    // canPlace(d)를 여러 번 호출할 때 간선 판정을 다시 계산하지 않아도 된다.
    for (int d = 1; d <= maxDist; d++) {
        for (int i = 0; i < totalLocker; i++) {
            adjByDist[d][i].reset();
            for (int j = 0; j < totalLocker; j++) {
                if (i != j && distTable[i][j] >= d) {
                    adjByDist[d][i].set(j);
                }
            }
        }
    }

    int left = 1, right = maxDist, answer = 0;

    // "d 이상으로 배치 가능"은 단조성이 있으므로
    // 큰 거리에서 안 되면 더 큰 거리도 안 된다.
    // 따라서 전체 탐색 대신 이분탐색으로 검사 횟수를 줄인다.
    while (left <= right) {
        int mid = (left + right) / 2;
        if (canPlace(mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}