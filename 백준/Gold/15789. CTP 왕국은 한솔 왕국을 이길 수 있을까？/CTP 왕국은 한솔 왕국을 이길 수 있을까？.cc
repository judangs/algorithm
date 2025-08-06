#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <set>

using namespace std;

int N, M, C, H, K;
int parent[100001];
int group[100001];

struct Node {
    int kingdom;
    int count;
    
    bool operator<(const Node & o) const {
        return count < o.count;
    }
};

int find(int now) {
    if(parent[now] == now) return now;
    return (parent[now] = find(parent[now]));
}

void merge(int a, int b) {
    a = find(a), b = find(b);
    if(a != b) {
        if(a > b) swap(a, b);
        parent[b] = a;
        group[a] += group[b];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        parent[i] = i; 
        group[i] = 1;
    }

    for(int i=0; i<M; i++) {
        int X, Y; 
        cin >> X >> Y;
        merge(X, Y);
    }

    cin >> C >> H >> K;

    priority_queue<Node, vector<Node>, less<Node>> pq;
    set<int> visited;
    
    for(int i=1; i<=N; i++) {
        int kingdom = find(i);
        if(kingdom != find(C) && kingdom != find(H) && visited.find(kingdom) == visited.end()) {
            pq.push({kingdom, group[kingdom]});
            visited.insert(kingdom);
        }
    }

    while(!pq.empty() && K > 0) {
        auto node = pq.top(); 
        pq.pop();
        
        if(find(node.kingdom) != find(C)) {
            merge(C, node.kingdom);
            K--;
        }
    }

    int answer = group[find(C)];
    cout << answer << endl;
    
    return 0;
}