#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

#define MAX_V 1201

using namespace std;

int M, N, pig;
int A, K, B;

int source = 0, sink = 1200;
int person = 1001;
int capacity[MAX_V][MAX_V], flow[MAX_V][MAX_V];
int want[101];
int first[1001];

vector<vector<int>> adj;
vector<vector<int>> visited;


int network_flow() {

    int answer = 0;
    while(true) {
        vector<int> parent(MAX_V, -1);

        queue<int> q;
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


void connect_edge(int s, int e, int cost) {
    adj[s].push_back(e), adj[e].push_back(s);
    capacity[s][e] = cost;
}

int main() {

    cin >> M >> N;
    
    visited.resize(101);
    adj.resize(MAX_V);

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));
    memset(want, 0, sizeof(want));
    memset(first, -1, sizeof(first));

    for(int i=1; i<=M; i++) {
        cin >> pig;
        connect_edge(i, sink, pig);
    }

    for(int i=1; i<=N; i++) {
        cin >> A;
        for(int j=0; j<A; j++) {
            cin >> K;
            visited[i].push_back(K);
            if(first[K] == -1) first[K] = i;
        }

        cin >> B;
        want[i] = B;
    }


    for(int i=1; i<=N; i++) {
        connect_edge(source, person + i, want[i]);

        for(auto v: visited[i]) {
            connect_edge(person + i, v, 1e9);
            if(first[v] != i) connect_edge(person + i, person + first[v], 1e9);
        }
    }


    cout << network_flow();
}