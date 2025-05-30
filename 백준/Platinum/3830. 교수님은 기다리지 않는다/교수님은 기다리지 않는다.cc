#include <iostream>
#include <vector>

using namespace std;

int N, M, a, b, w;
char opt;

vector<int> parent;
vector<long long> weight;

int find(int node) {
    if(parent[node] == node) return node;
    
    int p = find(parent[node]);
    weight[node] += weight[parent[node]];

    return parent[node] = p;
}

void merge(int a, int b, int cost) {
    int ra = find(a), rb = find(b);

    if(ra != rb) {
        weight[rb] = weight[a] - weight[b] + cost;
        parent[rb] = ra;
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    while(cin >> N >> M) {
        if(N == 0 && M == 0) break;

        parent.resize(N + 1);
        weight.assign(N + 1, 0ll);
        for(int node=0; node<=N; node++)
            parent[node] = node;

        for(int i=0; i<M; i++) {
            cin >> opt;
            if(opt == '!') {
                cin >> a >> b >> w;
                merge(a, b, w);
            }
            else {
                cin >> a >> b;
                if(find(a) != find(b)) cout << "UNKNOWN\n";
                else cout << (weight[b] - weight[a]) << "\n";
            }
        }
    }
}