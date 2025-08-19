#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;

const ll inf = 1e18;
int N, M, C;
vector<vector<pair<int, int>>> adj;

struct Node {
    int now;
    ll cost;

    bool operator>(const Node & o) const {
        return cost > o.cost;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> C;
    adj.resize(N + 1);
    ll total = 0;
    
    for(int i=0; i<M; i++) {
        int A, B, D; 
        cin >> A >> B >> D;
        adj[A].push_back({B, D}); 
        adj[B].push_back({A, D});
        total += D;
    }

    vector<ll> distance(N + 1, inf);
    vector<bool> visit(N + 1, false);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    distance[1] = 0;
    pq.push({1, 0});
    
    ll answer = inf;

    while(!pq.empty()) {
        auto node = pq.top(); 
        pq.pop();

        if(node.cost > distance[node.now]) continue;
        if(visit[node.now]) continue;

        visit[node.now] = true;

        for(auto next: adj[node.now]) {
            if(visit[next.first]) {
                total -= next.second;
            }
        }

        answer = min(answer, C * node.cost + total);

        for(auto next: adj[node.now]) {
            if(node.cost + next.second < distance[next.first]) {
                distance[next.first] = node.cost + next.second;
                pq.push({next.first, distance[next.first]});
            }
        }
    }

    cout << answer << endl;
}