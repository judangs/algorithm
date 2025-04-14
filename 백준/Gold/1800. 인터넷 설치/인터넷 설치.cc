#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1e18

using namespace std;
typedef long long ll;

int N, P, K;
int s, e, c;

struct Node {
    int cur;
    ll cost;
    int line;
    int free;

    Node(int cur, ll cost, int line, int free): cur(cur), cost(cost), line(line), free(free) { }

    bool operator<(const Node & other) const {
        return cost > other.cost;
    }
};

vector<vector<pair<int, int>>> graph;
priority_queue<Node> pq;

int dijkstra(int start) {

    vector<vector<ll>> distance(N + 1, vector<ll>(N + 1, INF));
    distance[start][0] = 0;
    pq.push({start, 0, 0, 0});

    int answer = INT32_MAX;
    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();

        
        if(node.cur == N) {
            if(node.free <= K) {
                answer = min(answer, node.line);    
            }
            continue;
        }
        if(node.line > distance[node.cur][node.free]) continue;
        for(auto next: graph[node.cur]) {
            if(node.free < K && node.line < distance[next.first][node.free + 1]) {
                distance[next.first][node.free + 1] = node.line;
                pq.push({next.first, distance[next.first][node.free + 1], node.line, node.free + 1});
            }

            int next_line = max(node.line, next.second);
            if(next_line < distance[next.first][node.free]) {
                distance[next.first][node.free] = next_line;
                pq.push({next.first, distance[next.first][node.free], next_line, node.free});
            }
        }

    }

    return (answer == INT32_MAX ? -1 : answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> P >> K;

    graph.resize(N + 1);
    
    for(int i=0; i<P; i++) {
        cin >> s >> e >> c;
    
        graph[s].push_back({e, c});
        graph[e].push_back({s, c});
    }

    cout << dijkstra(1);
}
