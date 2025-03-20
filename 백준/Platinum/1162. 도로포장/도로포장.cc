#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, K;
int a, b;
long long c;

vector<vector<pair<int, long long>>> graph;

struct Node {
    long long cost;
    int wrap;
    int current;

    Node(long long cost, int wrap, int current): cost(cost), wrap(wrap), current(current) { }
};

struct compare {
    bool operator()(Node l, Node r) {
        return l.cost > r.cost;
    }
};

long long dijkstra() {

    priority_queue<Node, vector<Node>, compare> pq;
    vector<vector<long long>> dist(21, vector<long long>(N + 1, 1e18));
    
    dist[0][1] = 0;
    pq.push({0, 0, 1});
    
    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();
        
        if(node.current == N)
            return node.cost;


        if(node.cost > dist[node.wrap][node.current]) continue;
        for(auto next: graph[node.current]) {
            if(node.cost + next.second < dist[node.wrap][next.first]) {
                dist[node.wrap][next.first] = node.cost + next.second;
                pq.push({dist[node.wrap][next.first], node.wrap, next.first});
            }
            if(node.wrap < K) {
                if(node.cost < dist[node.wrap + 1][next.first]) {
                    dist[node.wrap + 1][next.first] = node.cost;
                    pq.push({dist[node.wrap + 1][next.first], node.wrap + 1, next.first});
                }
            }
        }
    }

    return 1e18;

}

int main() {
    
    cin >> N >> M >> K;

    graph.resize(N + 1);
    for(int i=0; i<M; i++) {
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }

    cout << dijkstra();
    
}