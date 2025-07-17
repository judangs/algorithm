#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1e9

using namespace std;

int N;
int cost[10001], indegree[10001];
vector<int> adj[10001];

int topological() {
    queue<int> q;
    vector<int> distance(N + 1, 0);

    for(int vertex=1; vertex <= N; vertex++) {
        if(indegree[vertex] == 0) {
            distance[vertex] = cost[vertex];
            q.push(vertex);
        }
    }

    int answer = 0;
    while(!q.empty()) {
        int now = q.front(); q.pop();

        answer = max(answer, distance[now]);

        for(auto next: adj[now]) {
            indegree[next]--;
            distance[next] = max(distance[next], distance[now] + cost[next]);
            if(indegree[next] == 0) {
                q.push(next);
            }
        }
    }

    return answer;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int work=1; work<=N; work++) {
        int time, count; cin >> time >> count;
        cost[work] = time;
        for(int i=0; i<count; i++) {
            int pre; cin >> pre;
            if(pre == 0) continue;

            indegree[work]++;
            adj[pre].push_back(work);
        }
    }

    cout << topological();
}