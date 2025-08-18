#include <iostream>
#include <vector>
#include <queue>

#define INF 1e9

using namespace std;
typedef pair<int, int> pii;

int T;

struct compare {
    bool operator()(pii & l, pii & r) {
        return l.second > r.second;
    }
};

int dijkstra(int n, int start, vector<vector<pii>> & adj, vector<int> & friends) {

    vector<int> distance(n + 1, INF);
    
    priority_queue<pii, vector<pii>, compare> pq;
    distance[start] = 0;
    pq.push({start, 0});

    while(!pq.empty()) {
        auto now = pq.top(); pq.pop();

        if(now.second > distance[now.first]) continue;
        for(auto next: adj[now.first]) {
            if(now.second + next.second < distance[next.first]) {
                distance[next.first] = now.second + next.second;
                pq.push({next.first, distance[next.first]});
            }
        }
    }

    int ret = 0;
    for(auto room: friends) {
        ret += distance[room];
    }

    return ret;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {
        
        int N, M; cin >> N >> M;
        vector<vector<pair<int, int>>> adj(N + 1);

        for(int i=0; i<M; i++) {
            int start, end, cost; cin >> start >> end >> cost;
            adj[start].push_back({end, cost});
            adj[end].push_back({start, cost});
        }

        int K; cin >> K;
        vector<int> friends(K);
        for(int i=0; i<K; i++) cin >> friends[i];

        int answer, mindist = INF;
        for(int room=1; room<=N; room++) {
            int distance = dijkstra(N, room, adj, friends);
            if(distance < mindist) {
                mindist = distance; answer = room;
            }
        }

        cout << answer << endl;
    }
}