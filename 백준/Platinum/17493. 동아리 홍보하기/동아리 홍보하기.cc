#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int include = 0, exclude = 1, none = 2;
int N, M;
int answer = 0;
vector<int> adj[200001];


int dfs(int now, vector<bool> & visit) {
    
    visit[now] = true;

    vector<bool> state(3, false);
    for(auto child: adj[now]) {
        if(visit[child]) continue;
        state[dfs(child, visit)] = true;
    }

    if(state[exclude]) {
        answer++;
        return include;
    }
    if(state[include]) return none;
    return exclude;
}



int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    while(M--) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<bool> visit(N + 1, false);
    for(int node=1; node<=N; node++) {
        if(!visit[node] && dfs(node, visit) == exclude) {
            answer++;
        }
    }

    cout << answer << endl;

}