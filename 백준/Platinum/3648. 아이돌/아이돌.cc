#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>


using namespace std;

int n, m;
int a, b;
int id, group;

stack<int> st;

int scc(int current, vector<vector<int>> & adj, vector<bool> & visited, vector<int> & node2id, vector<int> & node2scc) {
    visited[current] = true;
    st.push(current);
    int parent = node2id[current] = id++;
    
    for(auto next: adj[current]) {
        if(!visited[next]) parent = min(parent, scc(next, adj, visited, node2id, node2scc));
        else if(node2scc[next] == -1) parent = min(parent, node2id[next]);
    }

    if(parent == node2id[current]) {
        while(!st.empty()) {
            auto node = st.top();
            st.pop();
            
            node2scc[node] = group;
            
            if(node == current) break;
        }

        group++;
    }

    return parent;
}

vector<int> build_tarjan_scc(vector<vector<int>> & graph) {

    vector<bool> visited(2 * n + 2, false);
    vector<int> node2id(2 * n + 2);
    vector<int> node2scc(2 * n + 2, -1);

    for(int node = 2; node <=2 * n + 1; node++) {
        if(!visited[node])
            scc(node, graph, visited, node2id, node2scc);
    }

    return node2scc;
}

string solveSAT(vector<int> & node2scc) {

    int cheat = 1;
    if(node2scc[2 * cheat] > node2scc[2 * cheat + 1])
        return "no\n";

    for(int node=1; node<=n; node++) {
        if(node2scc[2 * node] == node2scc[2 * node + 1])
            return "no\n";
    }

    return "yes\n";
}

int main() {

    while(cin >> n >> m) {

        vector<vector<int>> adj(2 * n + 2);
        id = 0, group = 0;

        int not_a, not_b;
        for(int idx=0; idx<m; idx++) {
            cin >> a >> b;

            not_a = 2 * abs(a) + (a > 0);
            a = 2 * abs(a) + (a < 0);
            
            not_b = 2 * abs(b) + (b > 0);
            b = 2 * abs(b) + (b < 0);

            adj[not_a].push_back(b);
            adj[not_b].push_back(a);
        }
        
        a = 1;
        not_a = 2 * a + 1, a = 2 * a;
        adj[not_a].push_back(a);

        vector<int> scc = build_tarjan_scc(adj);
        cout << solveSAT(scc);
    }
}