#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<vector<int>> graph;
bool visit[18][18][18] = {false, };
int answer = 0;


void dfs(vector<int> & info, int current, int sheep, int wolf) {
    if(visit[current][sheep][wolf] == true) return;
    visit[current][sheep][wolf] = true;

    int next_sheep = sheep, next_wolf = wolf;
    int backup = info[current];
    if(info[current] == 0) next_sheep++;
    else if(info[current] == 1) next_wolf++;
    info[current] = 2;
    
    if(next_sheep > next_wolf) {
        answer = max(answer, next_sheep);
        for(int next: graph[current]) {
            dfs(info, next, next_sheep, next_wolf);
        }
    }

    info[current] = backup;
    visit[current][sheep][wolf] = false;
}

int solution(vector<int> info, vector<vector<int>> edges) {
    graph.resize(info.size());

    for(auto edge: edges) {
        graph[edge.front()].push_back(edge.back());
        graph[edge.back()].push_back(edge.front());
    }

    dfs(info, 0, 0, 0);
    return answer;
}