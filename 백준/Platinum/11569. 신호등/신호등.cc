#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

#define INF 987654321987654321

using namespace std;

int T, N, M, S, D;
int a, b;
long long c;

struct Node {
    long long time;
    int prev;
    int current;

    Node(long long time, int prev, int current): time(time), prev(prev), current(current) {}
};

struct compare {
    bool operator()(Node l, Node r) {
        return l.time > r.time;
    }
};


long long dijkstra(int start, vector<vector<pair<int, long long>>> graph, vector<int> delay) {

    priority_queue<Node, vector<Node>, compare> pq;
    vector<long long> dist(N + 1, INF);
    
    dist[start] = 0;
    for(auto next: graph[start]) {
        dist[next.first] = next.second;
        pq.push({dist[next.first], start, next.first});
    }

    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();

        if(node.current == D)
            return node.time;


        for(auto next: graph[node.current]) {
            int size = graph[node.current].size();
            int path = (node.time / delay[node.current]) % size;

            int order;
            for(order = 0; order < graph[node.current].size(); order++) {
                if(graph[node.current][order].first == node.prev) break;
            }

            if(order != path) {
                int multiple = (order + size - path) % size;
                long long wait = (node.time / delay[node.current] + multiple) * delay[node.current];
                node.time = wait;
            }

            if(node.time + next.second < dist[next.first]) {
                dist[next.first] = node.time + next.second;
                pq.push({dist[next.first], node.current, next.first});
            }
        }
    }

    return dist[D];
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while(T--) {

        cin >> N >> M >> S >> D;

        vector<vector<pair<int, long long>>> graph(N + 1);
        vector<int> delay(N + 1);
        for(int i=0; i<M; i++) {
            cin >> a >> b >> c;
            
            graph[a].push_back({b, c});
            graph[b].push_back({a, c});
        }
        
        for(int node=1; node<=N; node++) {
            cin >> delay[node];
            sort(graph[node].begin(), graph[node].end());
        }

        long long answer = dijkstra(S, graph, delay);
        cout << (answer != INF ? answer : -1) << "\n";
    }

}