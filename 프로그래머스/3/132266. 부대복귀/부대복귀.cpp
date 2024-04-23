#include <string>
#include <vector>
#include <queue>

using namespace std;

#define INF 1e18

vector<unsigned long long> dist;
vector<vector<int>> graph;

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
            if(cost + 1 < dist[next]) {
                dist[next] = cost + 1;
                q.push(make_pair(next, cost + 1));
            }
        }
    }
}

vector<int> solution(int n, vector<vector<int>> roads, vector<int> sources, int destination) {
    dist.resize(n  + 1, INF);
    graph.resize(n + 1);

    for(auto road: roads) {
        int end = road[0];
        int start = road[1];

        graph[start].push_back(end);
        graph[end].push_back(start);
    }


    dijkstra(destination);

    vector<int> answer;
    for(int source: sources) {
        if(dist[source] == INF) {
            answer.push_back(-1);
        }
        else {
            answer.push_back(dist[source]);
        }
    }

    return answer;
}