#include <string>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> graph;
vector<bool> visit;

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visit[start] = true;
    
    while(!q.empty()) {
        int current = q.front();
        
        q.pop();
        
        for(int next: graph[current]) {
            if(visit[next] == false) {
                visit[next] = true;
                q.push(next);
            }
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    graph.resize(n);
    visit.resize(n, false);
    
    for(int i=0; i<computers.size(); i++) {
        for(int j=0; j<computers[i].size(); j++) {
            if(i == j) continue;
            if(computers[i][j] == 1) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    
    int answer = 0;
    for(int i=0; i<n; i++) {
        if(visit[i] == false) {
            bfs(i);
            answer++;
        }
    }
    
    return answer;
}