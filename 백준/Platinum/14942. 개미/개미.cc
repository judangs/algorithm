#include <iostream>
#include <vector>
#include <memory.h>
#include <cmath>

#define MAXNODE 100001
#define INF 1e18

using namespace std;
typedef long long ll;
typedef pair<int, ll> pll;

int n, e, a, b, c;
int ant[MAXNODE];
vector<pll> adj[MAXNODE];
vector<vector<pll>> parent;

void dfs(int current, int prev) {

    for(auto next: adj[current]) {
        if(next.first != prev) {
            parent[0][next.first] = {current, next.second};
            dfs(next.first, current);
        }
    }
}


int query(int depth, int room, ll amount) {

    for(int k=depth; k>=0; k--) {
        if(parent[k][room].second <= amount) {
            amount -= parent[k][room].second;
            room = parent[k][room].first;
        }
    }

    if(room == 0) return 1; 
    return room;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    memset(ant, 0, sizeof(ant));

    cin >> n;
    for(int i=1; i<=n; i++) cin >> ant[i];
    for(int i=1; i<n; i++) {
        cin >> a >> b >> c;
        adj[a].push_back({ b, c });
        adj[b].push_back({ a, c });
    }
    
    int depth = ceil(log2(n + 1));
    parent.resize(depth + 1, vector<pll>(n + 1, {0, 0}));

    dfs(1, 0);
    for(int k=1; k<=depth; k++) {
        for(int room=1; room<=n; room++) {
            parent[k][room].first = parent[k - 1][parent[k - 1][room].first].first;
            parent[k][room].second = parent[k - 1][parent[k - 1][room].first].second + parent[k - 1][room].second;
        }
    }

    parent[0][1] = {0, INF};
    for(int q=1; q<=n; q++) {
        cout << query(depth, q, ant[q]) << "\n";
    }
}