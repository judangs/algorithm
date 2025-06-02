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
int cost[MAXNODE][MAXNODE];

queue<int> q;

void connect_vertex(int s, int e, int cap, int c) {
    adj[s].push_back(e), adj[e].push_back(s);
    capacity[s][e] = cap;
    cost[s][e] = c, cost[e][s] = -c;
}


int network_flow() {
    
    int sum = 0;
    while(true) {
        
        vector<int> parent(MAXNODE, -1);
        vector<int> distance(MAXNODE, INF);
        vector<int> is_in_queue(MAXNODE, false);

        parent[source] = source;
        distance[source] = 0;
        is_in_queue[source] = true;
        q.push(source);
        
        while(!q.empty()) {
            auto current = q.front(); q.pop();
            is_in_queue[current] = false;
            
            for(auto next: adj[current]) {
                if(capacity[current][next] - flow[current][next] > 0 
                    && distance[current] + cost[current][next] < distance[next]) {
                        distance[next] = distance[current] + cost[current][next];
                        parent[next] = current;
                        if(!is_in_queue[next]) {
                            is_in_queue[next] = true;
                            q.push(next);
                        }
                }
            }
        }

        if(parent[sink] == -1) break;

        int amount = INF;
        for(int node=sink; node!=source; node=parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for(int node=sink; node!=source; node=parent[node]) {
            sum += amount * cost[parent[node]][node];
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }        
    }

    return sum;
}

int main() {

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(cost, 0, sizeof(cost));

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        cin >> A;
        connect_vertex(i, sink, A, 0);
    }

    for(int i=1; i<=M; i++) {
        cin >> B;
        connect_vertex(source, storeidx + i, B, 0);
    }

    for(int i=1; i<=M; i++) {
        for(int j=1; j<=N; j++) {
            cin >> C;
            connect_vertex(storeidx + i, j, INF, C);
        }
    }

    cout << network_flow() << "\n";
}