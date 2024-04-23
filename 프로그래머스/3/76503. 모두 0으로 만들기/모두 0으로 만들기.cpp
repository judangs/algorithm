#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

vector<long long> node;
vector<vector<int>> graph;
vector<bool> visit;

long long answer = 0;

void dfs(int current) {
    for(auto next: graph[current]) {
        if(visit[next] == false) {
            visit[next] = true;
            dfs(next);
            node[current] += node[next];
            answer += abs(node[next]);
            node[next] = 0;
            
        }
    }
} 

long long solution(vector<int> a, vector<vector<int>> edges) {
    graph.resize(a.size());
    visit.resize(a.size(), false);
    
    for(int i=0; i<a.size(); i++)
        node.push_back(a[i]);
    
    for(auto edge: edges) {
        int start = edge[0];
        int end = edge[1];

        graph[start].push_back(end);
        graph[end].push_back(start);
    }

    int root_node = 0;
    dfs(root_node);

    if(node[root_node] == 0)
        return answer;
    else
        return -1;
}