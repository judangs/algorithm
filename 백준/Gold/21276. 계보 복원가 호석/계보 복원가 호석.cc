#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef pair<int, int> pii;

int N, M;
vector<string> names;
map<string, int> toidx;
map<int, string> ridx;
vector<vector<int>> adj;
vector<int> indegree;
map<int, vector<int>> children;



void solve(vector<string> root) {

    queue<int> q;
    for(auto name: root)
        q.push(toidx[name]);

    while(!q.empty()) {
        auto now = q.front(); q.pop();
        
        for(auto next: adj[now]) {
            indegree[next]--;
            if(indegree[next] == 0) {
                children[now].push_back(next);
                q.push(next);
            }
        }
    }

}


int main() {

    fastio;
    cin >> N;
    names = vector<string>(N);
    adj = vector<vector<int>> (N);
    indegree = vector<int> (N, 0);

    for(auto & name: names) cin >> name;

    sort(names.begin(), names.end());
    int idx = 0;
    for(auto & name: names) {
        toidx[name] = idx;
        ridx[idx] = name;
        idx++;
    }
    
    cin >> M;
    for(int i = 0; i < M; i++) {
        string X, Y; cin >> X >> Y;
        adj[toidx[Y]].push_back(toidx[X]);
        indegree[toidx[X]]++;
    }

    vector<string> root;
    for(auto name: names) {
        if(indegree[toidx[name]] == 0) 
            root.push_back(name);
    }

    solve(root);
    cout << root.size() << '\n';
    for(auto name: root) cout << name << ' ';
    cout << '\n';

    for(auto name: names) {
        if(children.find(toidx[name]) == children.end())
            children[toidx[name]] = { };
    }

    for(auto iter = children.begin(); iter != children.end(); iter++) {
        cout << ridx[iter->first] << ' ' << iter->second.size() << ' ';

        sort(iter->second.begin(), iter->second.end());

        for(auto child: iter->second) 
            cout << ridx[child] << ' ';
        cout << '\n';
    }
    

}