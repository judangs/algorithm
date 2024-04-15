#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#include <iostream>

using namespace std;

vector<vector<int>> graph;

int bfs(pair<int, int> pass, int n) {
    vector<int> visit(n + 1, false);

    vector<int> ret;
    for(int i=1; i<visit.size(); i++) {
        if(visit[i] == false) {
            queue<int> q;
            visit[i] = true;
            q.push(i);
            
            int cost = 0;
            while(!q.empty()) {
                
                int current = q.front();

                q.pop();
                cost++;
                
                for(int next: graph[current]) {
                    if(current == pass.first && next == pass.second) continue;
                    if(current == pass.second && next == pass.first) continue;
                    if(visit[next] == false) {
                        visit[next] = true;
                        q.push(next);
                    }
                }
            }
            ret.push_back(cost);
        }
    }

    return abs(ret[0] - ret[1]);
}

int solution(int n, vector<vector<int>> wires) {
    graph.resize(n + 1);
    
    for(auto wire: wires) {
        graph[wire[0]].push_back(wire[1]);
        graph[wire[1]].push_back(wire[0]);
    }

    int answer = INT32_MAX;
    for(auto wire: wires) {
        pair<int, int> pass = make_pair(wire[0], wire[1]);
        answer = min(answer, bfs(pass, n));
    }

    return answer;
}