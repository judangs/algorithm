#include <iostream>
#include <vector>
#include <set>

using namespace std;

int id = 0;
int V, E;
vector<int> adj[100001];
int order[100001];

set<pair<int, int>> bridges;


int ordering(int now, int parent) {

    order[now] = ++id; int top = order[now];

    for(auto child: adj[now]) {
        if(child == parent) continue;
        if(!order[child]) {
            int super = ordering(child, now);

            if(order[now] < super) {
                if(now < child)
                    bridges.insert({now, child});
                else
                    bridges.insert({child, now});
            }

            top = min(top, super);
        }
        else {
            top = min(top, order[child]);
        }
    }

    return top;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> V >> E;
    for(int i=0; i<E; i++) {
        int A, B; cin >> A >> B;
        adj[A].push_back(B), adj[B].push_back(A);
    }

    for(int vertex=1; vertex <= V; vertex++)
        if(!order[vertex])
            ordering(vertex, 0);

    cout << bridges.size() << endl;
    for(auto bridge: bridges) 
        cout << bridge.first << " " << bridge.second << "\n";
    cout << endl;
    
    
}