#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

int N, M, a, b;
int group = 0;
int id = 0;
vector<vector<int>> adj;

vector<vector<int>> _scc;
vector<bool> visited;
vector<int> isScc;
vector<int> nodeid;

stack<int> st;


int scc(int current) {

    visited[current] = true;
    st.push(current);
    int parent = nodeid[current] = id++;

    for(auto next: adj[current]) {
        if(!visited[next]) parent = min(parent, scc(next));
        else if(isScc[next] == -1) parent = min(parent, nodeid[next]);
    }

    if(parent == nodeid[current]) {
        while(!st.empty()) {
            auto node = st.top();
            st.pop();
            
            _scc[group].push_back(node);
            isScc[node] = group;
            
            if(node == current) break;
        }

        group++;
    }

    return parent;
}

void make_scc() {

    _scc.resize(2 * N + 2);
    visited.resize(2 * N + 2, false);
    isScc.resize(2 * N + 2, -1);
    nodeid.resize(2 * N + 2);
    
    for(int node=1; node<=2 * N; node++) {
        if(!visited[node])
            scc(node);
    }
}

int solveSAT() {
    for(int node=1; node <= N; node++) {
        if(isScc[2 * node] == isScc[2 * node + 1])
            return 0;
    }

    return 1;
}

int main() {

    cin >> N >> M;

    adj.resize(2 * N + 2);

    int not_a, not_b;
    for(int idx=0; idx<M; idx++) {
        cin >> a >> b;

        if(a < 0) {
            not_a = 2 * abs(a);
            a = 2 * abs(a) + 1;
        }
        else {
            not_a = 2 * a + 1;            
            a = 2 * a;
        }

        if(b < 0) {
            not_b = 2 * abs(b);
            b = 2 * abs(b) + 1;
        }
        else {
            not_b = 2 * b + 1;
            b = 2 * b;
        }

        adj[not_a].push_back(b);
        adj[not_b].push_back(a);
    }

    make_scc();
    cout << solveSAT();
    
}