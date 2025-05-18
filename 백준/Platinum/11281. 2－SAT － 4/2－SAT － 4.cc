#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int N, M, a, b;
int id = 0, group = 0;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> node2id;
vector<int> node2scc;
vector<vector<int>> _scc;

stack<int> st;

int scc(int current) {

    visited[current] = true;
    st.push(current);
    int parent = node2id[current] = id++;
    
    for(auto next: adj[current]) {
        if(!visited[next]) parent = min(parent, scc(next));
        else if(node2scc[next] == -1) parent = min(parent, node2id[next]);
    }

    if(parent == node2id[current]) {
        while(!st.empty()) {
            auto node = st.top();
            st.pop();
            
            _scc[group].push_back(node);
            node2scc[node] = group;
            
            if(node == current) break;
        }

        group++;
    }

    return parent;
}

void build_tarjan_scc() {
    
    visited.resize(2 * N + 2, false);
    node2id.resize(2 * N + 2);
    node2scc.resize(2 * N + 2, -1);
    _scc.resize(2 * N + 2);

    for(int node=2; node<=2 * N + 1; node++) {
        if(!visited[node])
            scc(node);
    }
    
}

vector<int> solveSAT() {
    for(int node=1; node <= N; node++) {
        if(node2scc[2 * node] == node2scc[2 * node + 1])
            return vector<int>();
    }

    vector<pair<int, int>> order;
    for(int node=1; node<=N; node++) {
        order.push_back({ node2scc[2 * node], 2 * node });
        order.push_back({ node2scc[2 * node + 1], 2 * node + 1 });
    }

    sort(order.rbegin(), order.rend());
    vector<int> answer(N + 1, -1);
    for(auto o: order) {
        int node = o.second / 2, isTrue = (o.second % 2 == 0);
        if(answer[node] != -1) continue;
        answer[node] = !isTrue;
    }

    return answer;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    adj.resize(2 * N + 2);
    
    int not_a, not_b;
    for(int i=0; i<M; i++) {
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

    build_tarjan_scc();
    vector<int> result = solveSAT();

    if(result.empty()) {
        cout << "0";
    }
    else {
        cout << "1\n";
        for(int node=1; node<=N; node++) {
            cout << result[node] << " ";
        }
    }

}