#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N, M, A, B, C;

vector<vector<pair<int, int>>> adj;

struct Edge {
    int a, b, cost;
};
vector<Edge> edges;
vector<int> parent;

struct Node {
    int now;
    int distance;
    int fee;
};


int dijkstra() {

    vector<vector<int>> dist(N + 1, vector<int>(21, inf));
    queue<Node> q;
    dist[A][0] = 0;
    q.push({ A, 0, 0 });
    
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        if(node.distance > dist[node.now][node.fee]) continue;
        for(auto next: adj[node.now]) {
            int mfee = max(node.fee, next.second);
            if(node.distance + next.second < dist[next.first][mfee]) {
                dist[next.first][mfee] = node.distance + next.second;
                q.push({ next.first, dist[next.first][mfee], mfee});
            }
        }
    }

    for(int i = 0; i <= 20; i++) {
        if(dist[B][i] <= C)
            return i;
    }
    return -1;
}

int main() {

    fastio;
    cin >> N >> M >> A >> B >> C;
    adj = vector<vector<pair<int, int>>>(N + 1);
    edges = vector<Edge>(M);
    for(int i = 0; i< M; i++) {
        int s, e, c; cin >> s >> e >> c;
        edges[i] = { s, e, c};
        adj[s].push_back({ e, c });
        adj[e].push_back({ s, c });
    }

    int ans = dijkstra();
    cout << ans << '\n';

    
    


}