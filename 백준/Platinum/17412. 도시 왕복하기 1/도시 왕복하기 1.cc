#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>

using namespace std;

int N, P, a, b;
int capacity[401][401];

int network_flow() {

    int source = 1, sink = 2;
    int path = 0;
    while(true) {

        queue<int> q;
        vector<int> parent(N + 1, -1);

        parent[source] = source;
        q.push(source);

        while(!q.empty() && parent[sink] == -1) {
            auto current = q.front(); q.pop();
            
            for(int next=1; next<N + 1; next++) {
                if(capacity[current][next] == 1 && parent[next] == -1) {
                    parent[next] = current;
                    q.push(next);
                } 
            }
        }

        if(parent[sink] == -1) break;

        for(int node=sink; node != source; node = parent[node]) {
            capacity[parent[node]][node]--;
            capacity[node][parent[node]]++;
        }

        path++;
    }

    return path;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> P;
    memset(capacity, 0, sizeof(capacity));

    for(int i=0; i<P; i++) {
        cin >> a >> b;
        capacity[a][b] = 1;
    }

    cout << network_flow();
}