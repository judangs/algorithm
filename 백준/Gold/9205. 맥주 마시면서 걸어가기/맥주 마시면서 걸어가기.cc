#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int T, n;
struct Position {
    int x, y;
};

struct Node {
    int now;
    int cost;
};


bool rechable(vector<Position> & building, vector<pair<int, int>> * adj) {

    queue<Node> q;
    vector<bool> visit(n + 3, false);
    
    q.push({0, 0});
    visit[0] = true;

    while(!q.empty()) {
        auto node = q.front(); q.pop();
        
        for(auto next: adj[node.now]) {
            int distance = next.second;
            if(!visit[next.first]) {
                if(20 * 50 - (node.now % 50) >= (distance - node.now)) {
                    visit[next.first] = true;
                    q.push({next.first, node.now + distance});
                }
            }
        }
    }

    return visit[n + 1];
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {

        cin >> n;

        vector<Position> building;
        for(int i=0; i<n+2; i++) {
            int x, y; cin >> x >> y;
            building.push_back({x, y});
        }

        vector<pair<int, int>> adj[103];
        for(int i=0; i<n + 1; i++) {
            for(int j=i+1; j<n + 2; j++) {
                auto & s = building[i], & e = building[j];
                int distance = abs(s.x - e.x) + abs(s.y - e.y);
                adj[i].push_back({j, distance});
                adj[j].push_back({i, distance});
            }
        }

        if(rechable(building, adj)) 
            cout << "happy" << endl;
        else
            cout << "sad" << endl;

    }
}