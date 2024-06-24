#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef tuple<int, int, int> tii;

int T, N, K, D;
int X, Y, W;

vector<int> build_time;
vector<int> build;
vector<int> answer;
vector<vector<int>> graph;

priority_queue<int> pq;

int solve() {

    for(int i=1; i<=N; i++) {
        if(build[i] == 0) {
            answer[i] = build_time[i];
            pq.push(i);
        }
    }

    while(!pq.empty()) {

        int current = pq.top();
        pq.pop();

        for(int next: graph[current]) {
            if(build[next] > 0){
                answer[next] = max(answer[next], answer[current] + build_time[next]);
            }

            build[next]--;
            if(build[next] == 0) pq.push(next);
        }
    }
    
    return answer[W];
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for(int t=0; t<T; t++) {

        cin >> N >> K;

        build.resize(N + 1,  0);
        build_time.resize(N + 1);
        graph.resize(N + 1);
        answer.resize(N + 1, 0);

        for(int i=1; i<=N; i++) {
            cin >> D;
            build_time[i] = D;
        }

        for(int i=0; i<K; i++) {
            cin >> X >> Y;
            graph[X].push_back(Y);
            build[Y]++;
        }

        cin >> W;
        cout << solve() << "\n";

        graph.clear();
        answer.clear();
    }
}