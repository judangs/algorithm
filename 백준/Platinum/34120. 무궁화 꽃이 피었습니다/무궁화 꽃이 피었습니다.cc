#include <iostream>
#include <vector>
#include <queue>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

const ll inf = 1e18;
int N, M;
ll a, b;
vector<vector<pair<int, ll>>> adj;
vector<int> window;

struct Node {
    int now;
    ll time;
    
    bool operator>(const Node & o) const {
        return time > o.time;
    }
};

ll move(ll t, ll road_time, int dest, int now) {
    if (road_time > a) return -1;
    
    ll cycle = a + b;
    
    while(true) {
        ll pos = t % cycle;
        
        if(window[now] == 1 && a <= pos) return -1;
        if (a <= pos) {
            t += (cycle - pos);
            pos = 0;
        }
        
        ll remaining = a - pos;
        
        if (road_time > remaining) {
            if (window[now] == 1) return -1;
            t += remaining + b;
            continue;
        }
        
        ll arrival = t + road_time;
        ll arrival_pos = arrival % cycle;
        
        if (arrival_pos == 0 || arrival_pos == a) {
            if (window[dest] == 1) return -1;
        }
        
        return arrival;
    }
}

ll dijkstra(int start) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<ll> dist(N + 1, inf);
    dist[start] = 0;
    pq.push({start, 0});

    while(!pq.empty()) {
        auto node = pq.top();
        pq.pop();

        if(dist[node.now] < node.time) continue;
        
        for(auto [next_node, road_time]: adj[node.now]) {
            ll next_time = move(node.time, road_time, next_node, node.now);

            if (next_time == -1) continue;
            if(next_time < dist[next_node]) {
                dist[next_node] = next_time;
                pq.push({next_node, next_time});
            }
        }
    }

    if(dist[N] == inf) return -1;
    return dist[N];
}

int main() {
    fastio;

    cin >> N >> M;
    adj.resize(N + 1);
    window.resize(N + 1);
    
    for(int i = 0; i < M; i++) {
        int x, y;
        ll t;
        cin >> x >> y >> t;
        adj[x].push_back({y, t});
    }

    for(int i = 1; i <= N; i++) cin >> window[i];
    cin >> a >> b;

    ll answer = dijkstra(1);
    cout << answer << endl;
}