#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, C, W;
vector<vector<int>> graph;
vector<int> works;
vector<bool> visited;


bool dfs(int current) {
    
    for(auto next: graph[current]) {
        if(visited[next] == false) {
            visited[next] = true;
            
            if(works[next] == -1 || dfs(works[next])) {
                works[next] = current;
                return true;
            }
        }
    }

    return false;
}

int main() {

    cin >> N >> M;

    graph.resize(N + 1);
    for(int idx=0; idx<N; idx++) {
        cin >> C;
        for(int c=0; c<C; c++) {
            cin >> W;
            graph[idx + 1].push_back(W); 
        }
    }

    works.resize(M + 1, -1);
    visited.resize(M + 1, false);

    int answer = 0;
    for(int person=1; person <= N; person++) {
        fill(visited.begin(), visited.end(), false);
        if(dfs(person))
            answer++;
        
    }


    cout << answer;
}