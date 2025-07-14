#include <iostream>
#include <vector>
#include <memory.h>

#define MAXWORKER 100001

using namespace std;

int n, m, i, w, p;

vector<int> tree[MAXWORKER];
int praise[MAXWORKER];

void dfs(int node, int parent) {
    for(auto child: tree[node]) {
        if(child != parent) {
            praise[child] += praise[node];
            dfs(child, node);
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    memset(praise, 0, sizeof(praise));
    
    cin >> n >> m;
    for(int child=1; child<=n; child++) {
        cin >> p; 
        if(p != -1) tree[p].push_back(child); 
    }

    for(int q=0; q<m; q++) {
        cin >> i >> w; praise[i] += w;
    }

    dfs(1, 0);
    for(int node=1; node<=n; node++) cout << praise[node] << " ";
    


}
