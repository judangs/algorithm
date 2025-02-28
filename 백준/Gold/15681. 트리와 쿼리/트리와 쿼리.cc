#include <iostream>
#include <vector>

#define MAX_VNODE 100001

using namespace std;

int N, R, Q, U;
int s, e;
vector<int> tree[MAX_VNODE];
vector<int> subtree;

int dfs(int current, int parent) {
    
    int child = 1;

    for(auto next: tree[current]) {
        if(next != parent) {
            child += dfs(next, current);
            
        }
    }

    subtree[current] = child;
    return child;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> R >> Q;

    subtree.resize(MAX_VNODE);
    for(int i=0; i< N - 1; i++) {
        cin >> s >> e;
        tree[s].push_back(e);
        tree[e].push_back(s);
    }

    dfs(R, 0);
    for(int query=0; query<Q; query++) {
        cin >> U;
        cout << subtree[U] << "\n";
    }
}