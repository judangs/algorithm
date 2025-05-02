#include <iostream>
#include <vector>
using namespace std;
 
int N, M;
int par[100001][21];//부모 노드를 저장
int depth[100001];
vector<int> tree[100001];
bool visited[100001];
 
void dfs(int n) {//DFS를 통해 부모노드, depth를 탐색
    visited[n] = true;
 
    for (int i = 0; i < tree[n].size(); i++) {
        int now = tree[n][i];
        if (!visited[now]) {
            par[now][0] = n;
            depth[now] = depth[n] + 1;
            dfs(now);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    cin >> N;
    for (int i = 0; i < N-1; i++) {
        int x, y;
        cin >> x >> y;
        tree[y].push_back(x);
        tree[x].push_back(y);
    }
    dfs(1);
    
    for(int j = 1; j < 17 ; j++){
        for (int i = 1; i <= N; i++) {
            int tmp = par[i][j - 1];
            par[i][j] = par[tmp][j - 1];
        }
    }
    cin >> M;
    while (M--) {
        int a, b;
        cin >> a >> b;
        if (depth[a] < depth[b]) swap(a, b);//편의상 더 깊이가 깊은 쪽을 a로 설정
        int gap = depth[a] - depth[b];
        for (int i = 20; i >= 0; i--) {
            if (gap >= (1 << i)) {
                gap -= (1 << i);
                a = par[a][i];
            }
        }
        //a와 b의 깊이차이를 2^i씩 올리면서 맞춰줌
 
        if (a == b) {
            cout << a << '\n';
            continue;
        }
        else {
            for (int i = 20; i >= 0; i--) {
                if (par[a][i] != par[b][i]) {
                    a = par[a][i];
                    b = par[b][i];
                }
            }//a, b의 공통 조상을 찾아 나감. 이 때도 2^i씩 올리면서 업데이트
            cout << par[a][0] << '\n';
        }
        
    }
}
