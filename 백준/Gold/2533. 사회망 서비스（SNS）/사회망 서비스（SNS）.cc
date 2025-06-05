#include <iostream>
#include <vector>
#include <memory.h>

#define MAXNODE 1000001

using namespace std;

vector<int> tree[MAXNODE];
bool adaptor[MAXNODE];

int N, s, e;
int answer = 0;

void dfs(int current, int parent) {
    for(auto next: tree[current]) {
        if(next != parent) {
            dfs(next, current);
            if(!adaptor[current] && !adaptor[next]) {
                adaptor[current] = true;
                answer++;
            }
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    memset(adaptor, false, sizeof(adaptor));
    
    cin >> N;
    for(int i=1; i<=N - 1; i++) {
        cin >> s >> e;
        tree[s].push_back(e);
        tree[e].push_back(s);
    }

    dfs(1, 0);
    cout << answer;
}