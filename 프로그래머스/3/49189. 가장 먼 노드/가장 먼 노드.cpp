#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

#define INF 1e9

using namespace std;

vector<vector<int>> graph;
vector<int> dist;
queue<pair<int, int>> q;

void dijkstra(int start) {
    dist[start] = 0;
    q.push({start, 0});

    while(!q.empty()) {
        int current = q.front().first;
        int cost = q.front().second;

        q.pop();

        if(cost > dist[current]) continue;

        for(auto next: graph[current]) {
            if(cost + 1 < dist[next]) {
                dist[next] = cost + 1;
                q.push({next, cost + 1});
            }
        }
    }
}

int solution(int n, vector<vector<int>> edge) {
    graph.resize(n + 1);
    dist.resize(n + 1, INF);

    for(auto e: edge) {
        graph[e.front()].push_back(e.back());
        graph[e.back()].push_back(e.front());
    }

    dijkstra(1);
    int max_value = *max_element(dist.begin() + 1, dist.end());
    int answer = 0;
    for(int d: dist) {
        if(d == max_value) answer++;
    }

    return answer;
}