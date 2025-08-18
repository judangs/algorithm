#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, K;
bool station[1001];
int parent[1001];

struct Edge {
    int start, end, cost;

    bool operator<(const Edge & o) const {
        return cost < o.cost;
    }
};

int find(int now) {
    if(now == parent[now]) return now;
    return (parent[now] = find(parent[now]));
}

void merge(int a, int b) {

    a = find(a), b = find(b);

    if(a > b) swap(a, b);
    if(station[b]) parent[a] = b;
    else parent[b] = a;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> K;
    for(int i=0; i<=N; i++) parent[i] = i;
    for(int i=0; i<K; i++) {
        int city; cin >> city;
        station[city] = true;
    }

    vector<Edge> edges(M);
    for(int i=0; i<M; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges[i] = {u, v, w};
    }

    sort(edges.begin(), edges.end());
    
    int answer = 0;
    for(auto & [start, end, cost]: edges) {
        int s = find(start), e = find(end);
        if(station[s] && station[e]) continue;
        if(s == e) continue;
        
        merge(start, end);
        answer += cost;
    }

    cout << answer << endl;
}