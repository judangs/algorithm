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
};

int find(int a) {
    if(a == parent[a]) return a;
    return (parent[a] = find(parent[a]));
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if(a > b) swap(a, b);
    parent[b] = a;
}


int dijkstra() {

    vector<int> dist(N + 1, inf);
    queue<Node> q;
    dist[A] = 0;
    q.push({ A, 0 });
    
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        if(node.distance > dist[node.now]) continue;
        for(auto next: adj[node.now]) {
            if(node.distance + next.second < dist[next.first]) {
                dist[next.first] = node.distance + next.second;
                q.push({ next.first, dist[next.first]});
            }
        }
    }

    return dist[B];
}

int main() {

    fastio;
    cin >> N >> M >> A >> B >> C;
    adj = vector<vector<pair<int, int>>>(N + 1);
    edges = vector<Edge>(M);
    for(int i = 0; i< M; i++) {
        int s, e, c; cin >> s >> e >> c;
        edges[i] = { s, e, c};
    }

    sort(edges.begin(), edges.end(), [](const Edge & l, const Edge & r) {
        return l.cost < r.cost;
    });
    
    parent = vector<int>(N + 1);
    for(int i = 1; i <= N; i++) parent[i] = i;
    
    int ans = -1;
    for(int i = 0; i < M; i++) {
        int s = edges[i].a, e = edges[i].b, c = edges[i].cost;
        merge(s, e); adj[s].push_back({ e, c}); adj[e].push_back({ s, c });

        if(find(A) == find(B)) {
            if(dijkstra() <= C) {
                ans = edges[i].cost;
                break;
            }
        }
    }

    cout << ans << '\n';


}