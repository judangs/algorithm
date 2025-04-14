#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 1e9
#define SIZE 1001

using namespace std;

int S;
int answer;
vector<vector<bool>> visited(1001, vector<bool>(1001, false));

struct Node {
    int n;
    int clip;
    int time;
    
    bool operator<(const Node & other) const {
        return time > other.time;
    }
};

priority_queue<Node> pq;


int main() {
    cin >> S;

    visited[1][0] = 0;
    pq.push({1, 0, 0});

    while(!pq.empty()) {

        auto node = pq.top();
        pq.pop();

        if(node.n == S) {
            cout << node.time;
            break;
        }

        if(visited[node.n][node.n] == false) {
            visited[node.n][node.n] = true;
            pq.push({node.n, node.n, node.time + 1});
        }
        if(node.n + node.clip < SIZE && visited[node.n + node.clip][node.clip] == false) {
            visited[node.n + node.clip][node.clip] = true;
            pq.push({node.n + node.clip, node.clip, node.time + 1});
        } 
        if(1 < node.n - 1 && visited[node.n - 1][node.clip] == false) {
            visited[node.n - 1][node.clip] = true;
            pq.push({node.n - 1, node.clip, node.time + 1});
        }
    }
}