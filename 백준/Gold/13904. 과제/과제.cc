#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
#include <iostream>

using namespace std;

int N, d, w;

struct Assignment {
    int deadline;
    int score;
};

vector<Assignment> assignments;
int cache[1001][1001];

int assign(int day, int idx) {

    if(idx == N) return 0;
    if(cache[day][idx] != -1) return cache[day][idx];

    int & ret = cache[day][idx];
    ret = 0;


    ret = max(ret, assign(day, idx + 1));
    if(day <= assignments[idx].deadline)
        ret = max(ret, assignments[idx].score + assign(day + 1, idx + 1));

    
    return ret;
}

int main() {

    memset(cache, -1, sizeof(cache));

    cin >> N;
    int end = 0;
    for(int i=0; i<N; i++) {
        cin >> d >> w;
        assignments.push_back({ d, w });
        end = max(end, d);
    }

    sort(assignments.begin(), assignments.end(), [](const Assignment & l, const Assignment & r) {
        if(l.deadline == r.deadline)
            return l.score < r.score;
        return l.deadline < r.deadline;
    });

    cout << assign(1, 0) << "\n";
}