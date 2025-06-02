#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>

#define MAXNODE 250
#define INF 1e9

using namespace std;

int N, M, A, B, C;
int source = 0, sink = 201;
int storeidx = 100;

vector<int> adj[MAXNODE];
int capacity[MAXNODE][MAXNODE], flow[MAXNODE][MAXNODE];

queue<int> q;

void connect_vertex(int s, int e, int cap) {
    adj[s].push_back(e), adj[e].push_back(s);
    capacity[s][e] = cap;
}


int network_flow() {
    
    int answer = 0;
    while(true) {
        
        vector<int> parent(MAXNODE, -1);
        vector<int> distance(MAXNODE, INF);

        parent[source] = source;
        distance[source] = 0;
        q.push(source);
        
        while(!q.empty()) {
            auto current = q.front(); q.pop();
            
            for(auto next: adj[current]) {
                if(capacity[current][next] - flow[current][next] > 0 && parent[next] == -1) {
                    parent[next] = current;
                    q.push(next);
                }
            }
        }

        if(parent[sink] == -1) break;

        int amount = INF;
        for(int node=sink; node!=source; node=parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for(int node=sink; node!=source; node=parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }        

        answer += amount;
    }

    return answer;
}

int main() {

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        cin >> A;
        connect_vertex(source, i, A);
    }

    for(int i=1; i<=M; i++) {
        cin >> B;
        connect_vertex(storeidx + i, sink, B);
    }

    for(int i=1; i<=M; i++) {
        for(int j=1; j<=N; j++) {
            cin >> C;
            connect_vertex(j, storeidx + i, C);
        }
    }

    cout << network_flow() << "\n";
}