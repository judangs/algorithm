#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<vector<int>> dist;


void dijkstra(int start, int idx) {
    queue<pair<int, int>> q;
    dist[idx][start] = 0;
    q.push(make_pair(start, 0));
    
    while(!q.empty()) {
        int current = q.front().first;
        int cost = q.front().second;
        
        q.pop();
        
        if(cost > dist[idx][current])
            continue;
        
        for(auto next: graph[current]) {
            if(cost + next.second < dist[idx][next.first]) {
                dist[idx][next.first] = cost + next.second;
                q.push(make_pair(next.first, dist[idx][next.first]));
            }
        }
    }
    
}


int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    
    graph.resize(n + 1);
    dist.resize(3, vector<int>(n + 1, INT32_MAX));
    
    for(auto fare: fares) {
        int start = fare[0];
        int end = fare[1];
        int cost = fare[2];
        
        graph[start].push_back(make_pair(end, cost));
        graph[end].push_back(make_pair(start, cost));
    }
    
    dijkstra(s, 0);
    dijkstra(a, 1);
    dijkstra(b, 2);
    
    int answer = INT32_MAX;
    for(int i=1; i<=n; i++) {
        if(dist[0][i] == INT32_MAX || dist[1][i] == INT32_MAX || dist[2][i] == INT32_MAX)
            continue;
        
        answer = min(answer, dist[0][i] + dist[1][i] + dist[2][i]);
    }
    return answer;
}