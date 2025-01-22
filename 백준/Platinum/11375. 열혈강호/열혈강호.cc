#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, c, w;
vector<vector<int>> graph;
vector<bool> visit;
vector<int> match;

bool bin_match(int idx) {
    
    for(auto work: graph[idx]) {
        if(visit[work] == false) {
            visit[work] = true;
            
            int person = match[work];
            if(person == -1 || bin_match(person)) {
                match[work] = idx;
                return true;
            }
        }
    }
    
    return false;
}

int main() {
    
    cin >> N >> M;
    
    graph.resize(N + 1);
    visit.resize(M + 1, false);
    match.resize(M + 1, -1);
    
    for(int i=1; i<=N; i++) {
        cin >> c;
        for(int work=0; work<c; work++) {
            cin >> w;
            graph[i].push_back(w);
        }
    }
    
    int answer = 0;
    for(int person=1; person<=N; person++) {
        fill(visit.begin(), visit.end(), false);
        if(bin_match(person) == true) {
            answer++;
        }
    }
    
    cout << answer;
    
}