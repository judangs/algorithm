#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int K, N, M, f, t, b;
int source, sink;

vector<vector<int>> adj;
vector<vector<int>> capacity, flow;
vector<pair<int, int>> edges;

void add(int s, int e, int cost) {
    adj[s].push_back(e), adj[e].push_back(s);
    capacity[s][e] += cost;
    edges.push_back({ s, e });
}

void network_flow() {
    while(true) {
        queue<int> q;
        vector<int> parent(N + 1, -1);

        parent[source] = source;
        q.push(source);

        while(!q.empty() && parent[sink] == -1) {
            auto current = q.front(); q.pop();
            
            for(auto next: adj[current]) {
                if(capacity[current][next] - flow[current][next] > 0 && parent[next] == -1) {
                    parent[next] = current;
                    q.push(next);
                }
            }
        }

        if(parent[sink] == -1) break;

        int amount = 1e9;
        for(int node=sink; node != source; node=parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for(int node=sink; node != source; node=parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }
    }   
}


bool other_path(int s, int e) {
    queue<int> q;
    vector<int> parent(N + 1, -1);
    q.push(s);

    while(!q.empty() && parent[e] == -1) {
        auto current = q.front(); q.pop();
        
        for(auto next: adj[current]) {
            if(capacity[current][next] - flow[current][next] > 0 && parent[next] == -1) {
                parent[next] = current;
                q.push(next);
            }
        }
    }

    if(parent[e] == -1) return true;
    else return false;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);


    cin >> K;
    while(K--) {
        
        cin >> N >> M;
        source = 1, sink = N;

        adj.resize(N + 1);
        capacity.resize(N + 1, vector<int>(N + 1, 0));
        flow.resize(N + 1, vector<int>(N + 1, 0));

        for(int i=0; i<M; i++) {
            cin >> f >> t >> b;
            add(f, t, b);
        }

        network_flow();

        int answer = 0;
        for(auto edge: edges) {
            int s = edge.first, e = edge.second;
            if(other_path(s, e)) 
                answer++;
        }

        cout << answer << "\n";
        
        adj.clear();
        capacity.clear(), flow.clear();
        edges.clear();
    }
}