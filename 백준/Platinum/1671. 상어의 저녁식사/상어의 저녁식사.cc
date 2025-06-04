#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>

#define MAXNODE 102

using namespace std;

int N, a, b, c;
int source = 0, sink = MAXNODE - 1;

struct Shark {
    int size;
    int speed;
    int inteligence;

    bool operator==(const Shark & o) {
        return size == o.size && speed == o.speed && inteligence == o.inteligence;
    }
};

vector<Shark> sharks;

vector<vector<int>> adj;
int capacity[MAXNODE][MAXNODE], flow[MAXNODE][MAXNODE];

void connect(int s, int e, int cap) {
    adj[s].push_back(e), adj[e].push_back(s);
    capacity[s][e] = cap;
}

int network_flow() {

    int eaten = 0;
    while(true) {
        
        queue<int> q;
        vector<int> parent(MAXNODE, -1);
        parent[source] = source;
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

        int amount = 1e9;
        for(int node=sink; node!=source; node=parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for(int node=sink; node!=source; node=parent[node]) {
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }        

        eaten += amount;
    }

    return eaten;
}

int main() {

    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    cin >> N;
    adj.resize(MAXNODE);
    for(int i=0; i<N; i++) {
        cin >> a >> b >> c;
        sharks.push_back({ a, b, c});
    }

    for(int i=1; i<=N; i++) {
        connect(source, i, 2);
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            if(i == j) continue;
            auto  s = sharks[i], f = sharks[j];
            if(s == f && i < j) continue; 
            if(s.size >= f.size && s.speed >= f.speed && s.inteligence >= f.inteligence) { 
                connect(i + 1, 50 + j + 1, 1);
            }
        }
    }

    for(int i=1; i<=N; i++) {
        connect(50 + i, sink, 1);
    }

    int eaten = network_flow();
    cout << (N - eaten);
}