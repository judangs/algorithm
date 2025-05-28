#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_V 2003
#define INF 1e9

using namespace std;

int N, M, K;
int w, wa;

int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
vector<int> adj[MAX_V];

int network_flow(int source, int sink) {

    int work = 0;
    while(true) {
        queue<int> q;
        vector<int> parent(MAX_V, -1);
        
        parent[source] = source;
        q.push(source);

        while(!q.empty() && parent[sink] == -1) {
            auto current = q.front(); q.pop();

            for(auto next: adj[current]) {
                if((capacity[current][next] - flow[current][next]) > 0 && parent[next] == -1) {
                    parent[next] = current;
                    q.push(next);
                }                
            }
        }

        if(parent[sink] == -1) break;
        
        int amount = INF;
        for(int node=sink; node != source; node=parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for(int node=sink; node != source; node=parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }

        work += amount;
    }


    return work;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> K;
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    int source = 0, sink = 2001;
    adj[0].push_back(2002), adj[2002].push_back(0);
    capacity[0][2002] = K;

    for(int node=1; node<=N; node++) {
        cin >> w;

        adj[0].push_back(node), adj[2002].push_back(node);
        adj[node].push_back(0), adj[node].push_back(2002);

        capacity[0][node] = 1;
        capacity[2002][node] = K;

        for(int j=0; j<w; j++) {
            cin >> wa;

            adj[node].push_back(1000 + wa), adj[1000 + wa].push_back(sink);
            adj[1000 + wa].push_back(node), adj[sink].push_back(1000 + wa);

            capacity[node][1000 + wa] = 1;
            capacity[1000 + wa][sink] = 1;
        }
    }

    cout << network_flow(source, sink);

}