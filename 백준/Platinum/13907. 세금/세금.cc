#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1e18

using namespace std;

int N, M, K;
int S, D;
int a, b, w, p;

vector<vector<pair<int, int>>> graph;
vector<int> tax;
vector<vector<long long>> dist;

struct Node {
    int path;
    int current;
    long long cost;

    Node(int path, int current, long long cost): path(path), current(current), cost(cost) {}

    bool operator>(const Node & other) const {
        return cost > other.cost;
    }
};

void dijkstra() {
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist.resize(N + 10, vector<long long>(N + 1, INF));
    
    dist[0][S] = 0;
    pq.push({0, S, 0});

    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();

        if(node.cost > dist[node.path][node.current]) continue;
        for(auto next: graph[node.current]) {
            long long ncost = node.cost + next.second;
            if(node.path + 1 < N && ncost< dist[node.path + 1][next.first]) {
                dist[node.path + 1][next.first] = ncost;
                pq.push({node.path + 1, next.first, dist[node.path + 1][next.first]});
            }
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;
    cin >> S >> D;

    graph.resize(N + 1);
    tax.resize(K + 1);

    for(int i=0; i<M; i++) {
        cin >> a >> b >> w;

        graph[a].push_back({b, w});
        graph[b].push_back({a, w});
    }

    tax[0] = 0;
    for(int i=1; i<=K; i++) {
        cin >> p;
        tax[i] = tax[i - 1] + p;
    }

    dijkstra();
        
    for(int increase=0; increase<=K; increase++) {
        long long answer = INF;
        for(int path=0; path<=N; path++) {
            if(dist[path][D] != INF) {
                answer = min(answer, dist[path][D] + path * tax[increase]);
            }
        }    

        cout << answer << "\n";
    }
}