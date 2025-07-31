#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M, X;
vector<int> adj[100001];
vector<int> revadj[100001];


int bfs(int start, vector<int> * graph) {
    
    queue<int> q;
    vector<bool> visit(N + 1, false);
    visit[start] = true; q.push(start);

    int ret = 0;
    while(!q.empty()) {
        auto current = q.front(); q.pop();
        
        for(auto next: graph[current]) {
            if(!visit[next]) {
                ret++;
                visit[next] = true;
                q.push(next);
            }
        }
    }

    return ret;
    
}


int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> X;
    while(M--) {
        int A, B; cin >> A >> B;
        adj[A].push_back(B);
        revadj[B].push_back(A);
    }

    int front = bfs(X, revadj), back = bfs(X, adj);
    cout << (1 + front) << " " << (N - back) << endl;
    

}