#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

typedef pair<int, int> pii;

struct compare {
    bool operator()(pii a, pii b) {
        return a.second > b.second;
    }  
};

vector<vector<pii>> graph;
vector<bool> isSummit;
vector<int> intensity;
priority_queue<pii, vector<pii>, compare> pq;

vector<int> answer = {INT32_MAX, INT32_MAX};

void dijkstra(vector<int> & gates) {
    for(int gate: gates) {
        pq.push({gate, 0});
        intensity[gate] = 0;
    }

    while(!pq.empty()) {
        int current = pq.top().first;
        int cost = pq.top().second;

        pq.pop();

        if(isSummit[current] == true) {
            if(cost == answer[1] && current < answer[0]) {
                answer = {current, cost};
            }
            if(cost < answer[1]) {
                answer = {current, cost};
            }
        }

        if(cost > intensity[current]) continue;
        if(isSummit[current] == true) continue;

        for(auto next: graph[current]) {
            int next_cost = max(cost, next.second);
            if(intensity[next.first] == -1) {
                intensity[next.first] = next_cost;
                pq.push({next.first, intensity[next.first]});
            }
            else if(next_cost < intensity[next.first]) {
                intensity[next.first] = next_cost;
                pq.push({next.first, intensity[next.first]});
            }
        }
    }
}

vector<int> solution(int n, vector<vector<int>> paths, vector<int> gates, vector<int> summits) {
    graph.resize(n + 1);
    isSummit.resize(n + 1, false);
    intensity.resize(n + 1, -1);

    sort(summits.begin(), summits.end());

    for(auto path: paths) {
        int s = path[0];
        int e = path[1];
        int cost = path[2];

        graph[s].push_back({e, cost});
        graph[e].push_back({s, cost});
    }

    for(int summit: summits) {
        isSummit[summit] = true;
    }

    dijkstra(gates);

    return answer;
}