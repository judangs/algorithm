#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int, int>>> graph;
vector<int> dist;

void dijkstra(int start) {
    queue<pair<int, int>> q;
    dist[start] = 0;
    q.push(make_pair(start, 0));

    while(!q.empty()) {
        int current = q.front().first;
        int cost = q.front().second;

        q.pop();

        if(cost > dist[current]) continue;

        for(auto next: graph[current]) {
            if(dist[current] + next.second < dist[next.first]) {
                dist[next.first] = dist[current] + next.second;
                q.push(make_pair(next.first, dist[next.first]));
            }
        }
    }
}

int solution(int N, vector<vector<int>> road, int K) {

    graph.resize(N + 1);
    dist.resize(N + 1, INT32_MAX);

    for(auto r: road) {
        int start = r[0];
        int end = r[1];
        int cost = r[2];

        graph[start].push_back(make_pair(end, cost));
        graph[end].push_back(make_pair(start, cost));
    }

    dijkstra(1);

    int answer = 0;
    for(int i=1; i<dist.size(); i++) {
        if(dist[i] <= K)
            answer++;
    }

    return answer;
}