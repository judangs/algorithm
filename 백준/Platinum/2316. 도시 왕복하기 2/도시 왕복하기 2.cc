#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

#define MAX_V 900

using namespace std;

int N, P, a, b;
int source = 1, sink = 2;

vector<vector<int>> adj;

int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];

void connect(int s, int e, int cost) {
    adj[s].push_back(e), adj[e].push_back(s);
    capacity[s][e] = cost;
}

int network_flow() {

    int answer = 0;
    while(true) {

        queue<int> q;

        vector<int> parent(MAX_V, -1);
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

        for(int node=sink; node != source; node=parent[node]) {
            flow[parent[node]][node]++;
            flow[node][parent[node]]--;
        }
        
        answer++;
    }

    return answer;
}

int main() {

    cin >> N >> P;

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    adj.resize(MAX_V);
    
    for(int node=3; node<=N; node++)
        connect(2 * node, 2 * node + 1, 1);

    for(int i=0; i<P; i++) {

        auto get_in = [](int x) { return (x == 1 || x == 2) ? x : 2 * x; };
        auto get_out = [](int x) { return (x == 1 || x == 2) ? x : 2 * x + 1; };

        cin >> a >> b;
        int in_a = get_in(a), out_a = get_out(a), in_b = get_in(b), out_b = get_out(b);

        connect(out_a, in_b, 1);
        connect(out_b, in_a, 1);
    }

    cout << network_flow();

}