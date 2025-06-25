#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1e9

using namespace std;

int n, m, r, t;
int a, b, l;

struct Node {
    int current;
    int cost;

    bool operator>(const Node & o) const {
        return cost > o.cost;
    }
};

int field[101];
vector<pair<int,int>> adj[101];

int bfs(int start) {
    
    vector<int> distance(n + 1, INF);
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    distance[start] = 0;
    pq.push({start, 0});

    while(!pq.empty()) {
        auto node = pq.top(); pq.pop();

        for(auto next: adj[node.current]) {
            if(node.cost + next.second < distance[next.first]) {
                distance[next.first] = node.cost + next.second;
                pq.push({next.first, node.cost + next.second});
            }
        }
    }

    int item = 0;
    for(int i=1; i<=n; i++) 
        if(distance[i] <= m) item += field[i];

    return item;
}

int main() {
    
    cin >> n >> m >> r;
    for(int i=1; i<=n; i++) cin >> field[i];

    for(int i=0; i<r; i++) {
        cin >> a >> b >> l;
        adj[a].push_back({b, l}), adj[b].push_back({a, l});
    }

    int answer = 0;
    for(int start=1; start<=n; start++) {
        answer = max(answer, bfs(start));
    }
    
    cout << answer;
}