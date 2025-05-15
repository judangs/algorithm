#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int V, E, A, B;
vector<vector<int>> adj;
vector<vector<int>> revadj;
vector<vector<int>> scc;
stack<int> st;

void dfs(int current, vector<bool> & visit) {
    
    visit[current] = true;

    for(auto next: adj[current]) {
        if(!visit[next]) {
            dfs(next, visit);
        }
    }

    st.push(current);
}

void match(int current, int group, vector<bool> & visit) {

    visit[current] = true;
    scc[group].push_back(current);

    for(auto next: revadj[current]) {
        if(!visit[next]) {
            match(next, group, visit);
        }
    }
}

bool compare(vector<int> a, vector<int> b) {
    return a.front() < b.front();
}

int main() {

    cin >> V >> E;

    adj.resize(V + 1);
    revadj.resize(V + 1);

    for(int i=0; i<E; i++) {
        cin >> A >> B;
        adj[A].push_back(B);
        revadj[B].push_back(A);
    }

    vector<bool> visit(V + 1, false);
    for(int node=1; node <= V; node++) {
        if(!visit[node]) {
            dfs(node, visit);
        }
    }

    scc.resize(V + 1);
    fill(visit.begin(), visit.end(), false);

    int group = 1;
    while(!st.empty()) {
        auto node = st.top();
        st.pop();
        
        if(visit[node]) continue;

        match(node, group, visit);
        group++;
    }

    cout << (group - 1) << "\n";
    for(int g=1; g < group; g++) {
        sort(scc[g].begin(), scc[g].end());
    }

    sort(scc.begin() + 1, scc.begin() + group, compare);
    for(int g=1; g < group; g++) {
        for(auto node: scc[g]) {
            cout << node << " ";
        }

        cout << "-1\n";
    }
}