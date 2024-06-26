#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<int> degree;
vector<vector<int>> graph;

void solve() {

    vector<int> answer;

    queue<int> q;
    for(int i=1; i<=N; i++) {
        if(degree[i] == 0)
            q.push(i);
    }

    while(!q.empty()) {
        int current = q.front();
        answer.push_back(current);

        q.pop();

        for(int next: graph[current]) {
            degree[next]--;
            if(degree[next] == 0) {
                q.push(next);
            }
        }
    }

    if(answer.size() != N) {
        cout << "0";
    }
    else {
        for(int node: answer) {
            cout << node << "\n";
        }
    }
}

int main() {
    cin >> N >> M;
    
    degree.resize(N + 1, 0);
    graph.resize(N + 1);

    cin.ignore();

    int num, member;
    for(int i=0; i<M; i++) {
        cin >> num;
        queue<int> q;
        for(int j=0; j<num; j++) {
            cin >> member;
            q.push(member);
        }

        int current = q.front();
        q.pop();
        while(!q.empty()) {
            int next = q.front();
            q.pop();

            degree[next]++;
            graph[current].push_back(next);
            current = next;
        }
    }

    solve();
}