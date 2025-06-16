#include <iostream>
#include <vector>
#include <queue>

#define INF 1e9

using namespace std;

int N, K, M, s;

struct Node {
    int station;
    int cost;  
};
queue<Node> q;

int tracing(int s, int e, vector<vector<int>> & adj, vector<vector<int>> line) {

    vector<int> distance(N + 1, INF);
    distance[s] = 1;
    q.push({s, 1});

    while(!q.empty()) {
        auto node = q.front();
        q.pop();

        if(node.cost < distance[node.station]) continue;

        for(auto st: line[node.station]) {
            for(auto next: adj[st]) {
                if(node.cost + 1 < distance[next]) {
                    distance[next] = node.cost + 1;
                    q.push({next, distance[next]});
                }
            }
        }
    }

    return (distance[e] == INF ? -1 : distance[e]);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K >> M;

    vector<vector<int>> hyper(M);
    vector<vector<int>> tube(N + 1);
    for(int i=0; i<M; i++) {
        for(int k=0; k<K; k++) {
            cin >> s;    
            hyper[i].push_back(s);
            tube[s].push_back(i);
        }
    }

    cout << tracing(1, N, hyper, tube);
    

}