#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int N, M, A, B;
vector<int> indegree;
vector<vector<int>> graph;
priority_queue<int, vector<int>, greater<int>> pq;

vector<int> answer;

void  topological() {
    for(int node=1; node<=N; node++) {
        if(indegree[node] == 0) pq.push(node);
    }

    while(!pq.empty()) {
        int current = pq.top();

        pq.pop();

        answer.push_back(current);
        
        for(int next: graph[current]) {
            indegree[next]--;
            if(indegree[next] == 0)
                pq.push(next);
        }
    }
}

int main() {
    cin >> N >> M;
    
    indegree.resize(N + 1, 0);
    graph.resize(N + 1);
    
    for(int i=0; i<M; i++) {
        cin >> A >> B;
        graph[A].push_back(B);
        indegree[B]++;
    }

    topological();
    for(int node: answer) cout << node << " ";
    
}