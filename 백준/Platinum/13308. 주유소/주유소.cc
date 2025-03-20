#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
int a, b, c;
vector<int> oils;
vector<vector<pair<int, int>>> graph;

struct Node {
    int oil;
    int center;
    long long cost;
    int current;  

    Node(int oil, int center, long long cost, int current): oil(oil), center(center), cost(cost), current(current) { }
};

struct compare {
    bool operator()(Node l, Node r) {
        return l.cost > r.cost;
    }
};

long long dijkstra(int start) {
    vector<vector<long long>> dist(N + 1, vector<long long>(N + 1, 1e18));
    priority_queue<Node, vector<Node>, compare> pq;

    pq.push({oils[start], start, 0, start});

    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();

        if(node.current == N)
            return node.cost;

        for(auto next: graph[node.current]) {
            long long ncost = node.cost + (next.second * node.oil);
            if(ncost < dist[node.center][next.first]) {
                dist[node.center][next.first] = ncost;
                if(oils[next.first] <= node.oil) {
                    pq.push({oils[next.first], next.first, dist[node.center][next.first], next.first});
                }

                pq.push({node.oil, node.center, dist[node.center][next.first], next.first});                
            }
        }
    }
    
    return 1e18;
}

int main() {

    cin >> N >> M;

    oils.resize(N + 1);
    graph.resize(N + 1);

    for(int i=1; i<=N; i++) {
        cin >> oils[i];
    }


    for(int i=0; i<M; i++) {
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    cout << dijkstra(1);
    
}