#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory.h>

#define MAXNODE 850
#define INF 1e9

using namespace std;

int N, M, c, w, s;
int source = 0, sink = 801;
int workidx = 400;

int capacity[MAXNODE][MAXNODE], flow[MAXNODE][MAXNODE];
int salary[MAXNODE][MAXNODE];
vector<int> adj[MAXNODE];

queue<int> q;

void connect(int s, int e, int cap, int c) {
    adj[s].push_back(e), adj[e].push_back(s);
    capacity[s][e] = cap;
    salary[s][e] = c, salary[e][s] = -c;
}


pair<int, int> MCMF() {

    int minSalary = 0, work = 0;
    
    while(true) {

        vector<int> parent(MAXNODE, -1);
        vector<bool> is_in_queue(MAXNODE, false);
        vector<int> cost(MAXNODE, INF);

        parent[source] = source;
        is_in_queue[source] = true;
        cost[source] = 0;
        q.push(source);

        while(!q.empty()) {
            auto current = q.front(); q.pop();
            is_in_queue[current] = false;

            for(auto next: adj[current]) {
                if(capacity[current][next] - flow[current][next] > 0 &&
                    cost[current] + salary[current][next] < cost[next]) {
                        cost[next] = cost[current] + salary[current][next];
                        parent[next] = current;
                        if(!is_in_queue[next]) {
                            is_in_queue[next] = true;
                            q.push(next);
                        }
                    }
            }
        }

        if(parent[sink] == -1) break;

        int amount = INF;
        for(int node=sink; node!=source; node=parent[node]) {
            amount = min(amount, capacity[parent[node]][node] - flow[parent[node]][node]);
        }

        for(int node=sink; node!=source; node=parent[node]) {
            minSalary += amount * salary[parent[node]][node];
            flow[parent[node]][node] += amount;
            flow[node][parent[node]] -= amount;
        }

        work += amount;
    }

    return {work, minSalary};
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    

    for(int person=1; person<=N; person++) {
        
        connect(source, person, 1, 0);

        cin >> c;
        while(c--) {
            cin >> w >> s;
            connect(person, workidx + w, INF, s);
        }
    }

    for(int work=1; work<=M; work++) {
        connect(workidx + work, sink, 1, 0);
    }

    auto answer = MCMF();
    cout << answer.first << "\n";
    cout << answer.second << "\n";

}
