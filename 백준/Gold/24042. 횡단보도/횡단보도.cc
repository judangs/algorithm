#include <iostream>
#include <vector>
#include <queue>

#define INF 1e18

using namespace std;
typedef long long ll;

int N, M, A, B;

vector<vector<pair<int, int>>> graph;

struct Node {
    int cur;
    ll time;

    bool operator<(const Node & other) const {
        return time > other.time;
    }
};
priority_queue<Node> pq;

ll dijkstra(int start) {
    vector<ll> distance(N + 1, INF);
    distance[start] = 0;
    pq.push({start, 0});

    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        
        if(node.time > distance[node.cur]) continue;
        for(auto next: graph[node.cur]) {
            int wait = next.second - (node.time % M);
            if(wait < 0) wait += M;

            if(node.time + wait < distance[next.first]) {
                distance[next.first] = node.time + wait;
                pq.push({next.first, distance[next.first]});
            }
        }
    }

    return distance[N];
}

int main() {
    cin >> N >> M;

    
    graph.resize(N + 1);
    for(int idx=1; idx<=M; idx++) {
        cin >> A >> B;
        graph[A].push_back({B, idx});
        graph[B].push_back({A, idx});
    }

    cout << dijkstra(1);
}