#include <iostream>
#include <vector>
#include <queue>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N, M;
vector<vector<int>> adj;
vector<vector<int>> dist;

struct Node {
    int now;
    int cost;

    bool operator>(const Node & o) const {
        return cost > o.cost;
    }
};

void dijkstra(int start) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[start][start] = 0;
    pq.push({ start, 0 });

    while(!pq.empty()) {
        auto node = pq.top(); pq.pop();
        
        if(node.cost > dist[start][node.now]) continue;
        for(auto next: adj[node.now]) {
            if(node.cost + 2 < dist[start][next]) {
                dist[start][next] = node.cost + 2;
                pq.push({ next, dist[start][next] });
            }
        }
    }
}

int main() {

    fastio;

    cin >> N >> M;
    adj = vector<vector<int>> (N + 1);
    dist = vector<vector<int>>(N + 1, vector<int>(N + 1, inf));
    for(int i = 0; i < M; i++) {
        int A, B; cin >> A >> B;
        adj[A].push_back(B);
        adj[B].push_back(A);
    }
    
    for(int i = 1; i <= N; i++) dijkstra(i);
    
    int lo, hi, sum = inf;
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {

            int now = 0;
            for(int k = 1; k <= N; k++) {
                if(i == k || j == k) continue;
                now += min(dist[i][k], dist[j][k]);
            }

            if(now < sum) {
                sum = now;
                lo = i, hi = j;
            }
        }
    }

    cout << lo << ' ' << hi << ' ' << sum << '\n';


}