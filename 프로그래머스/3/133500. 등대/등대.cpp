#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> graph;
vector<vector<int>> dp;
vector<bool> light;

int answer = 0;

void dfs(int cur_node, int parent_node) {
    for(int next_node: graph[cur_node]) {
        if(next_node != parent_node) {
            dfs(next_node, cur_node); 
            if(light[next_node] == false && light[cur_node] == false) {
                light[cur_node] = true;
                answer++;
            }
        }
    }
}

int solution(int n, vector<vector<int>>lighthouse) {
    graph.resize(n);
    light.resize(n, false);

    for(int i=0; i<lighthouse.size(); i++) {
        int start = lighthouse[i][0] - 1;
        int end = lighthouse[i][1] - 1;
        
        graph[start].push_back(end);
        graph[end].push_back(start);
    }


    dfs(0, 0);
    return answer;
}