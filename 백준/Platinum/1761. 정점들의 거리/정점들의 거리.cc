#include <iostream>
#include <vector>
#include <memory.h>
#include <cmath>

#define MAXNODE 40001

using namespace std;
typedef long long ll;

int N, M, a, b, d;
int mdepth;
vector<pair<int, int>> adj[MAXNODE];
ll dist[MAXNODE];
int depth[MAXNODE];
int parent[21][MAXNODE];


void dfs(int current, int prev, ll cost, int d) {

    depth[current] = d;
    dist[current] = cost;
    parent[0][current] = prev;

    for(auto next: adj[current]) {
        if(next.first != prev) {
            dfs(next.first, current, cost + next.second, d + 1);
        }
    }
}

int LCA(int a, int b) {
    if(depth[a] > depth[b]) swap(a, b);

    for(int d=mdepth; d>=0; d--) {
        if(depth[b] - depth[a] >= (1 << d)) {
            b = parent[d][b];
        }
    }

    if(a == b) return a;

    for(int d=mdepth; d>=0; d--) {
        if(parent[d][a] != parent[d][b]) {
            a = parent[d][a];
            b = parent[d][b];
        }
    }

    if(a != b) return parent[0][a];
    else return a;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    
    memset(dist, 0, sizeof(dist));
    memset(parent, 0, sizeof(parent));
    memset(depth, 0, sizeof(depth));

    for(int i=1; i<N; i++) {
        cin >> a >> b >> d;
        adj[a].push_back({ b, d });
        adj[b].push_back({ a, d });
    }

    dfs(1, 0, 0ll, 0);

    mdepth = ceil(log2(N));

    for(int d=1; d<=mdepth; d++) {
        for(int node=1; node<=N; node++) {
            parent[d][node] = parent[d - 1][parent[d - 1][node]];
        }
    }

    cin >> M;
    for(int i=0; i<M; i++) {
        cin >> a >> b;
        cout << dist[a] + dist[b] - 2 * dist[LCA(a, b)] << "\n";
    }
}