#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

const ll inf = 1e18;
int N, M, A, B;
ll C;

vector<vector<pair<int, ll>>> adj;

struct Node {
    int now;
    ll distance;
};


bool dijkstra(ll limit) {

    vector<ll> dist(N + 1, inf);
    queue<Node> q;
    dist[A] = 0ll;
    q.push({ A, 0 });
    
    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        if(node.distance > dist[node.now]) continue;
        for(auto next: adj[node.now]) {
            if(node.distance + next.second < dist[next.first]) {
                if(next.second <= limit) {
                    dist[next.first] = node.distance + next.second;
                    q.push({ next.first, dist[next.first]});
                }
            }
        }
    }

    return (dist[B] <= C);
}

int main() {

    fastio;
    cin >> N >> M >> A >> B >> C;
    adj = vector<vector<pair<int, ll>>>(N + 1);
    for(int i = 0; i< M; i++) {
        int s, e;
        ll c; cin >> s >> e >> c;
        adj[s].push_back({ e, c });
        adj[e].push_back({ s, c });
    }

    ll lo = 0, hi = 1e14 + 1;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(dijkstra(mid))
            hi = mid;
        else
            lo = mid;
    }

    ll ans = (dijkstra(hi) ? hi : -1);
    cout << ans << '\n';

    
    


}