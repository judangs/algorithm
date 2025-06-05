#include <iostream>
#include <vector>
#include <algorithm>

#define MAXNODE 10001

using namespace std;

int N, a, b;
vector<int> tree[MAXNODE];
vector<vector<int>> dp;
int villeage[MAXNODE];

void dfs(int current, int parent) {

    for(auto next: tree[current]) {
        if(next != parent) {
            dfs(next, current);
            dp[current][1] += dp[next][0];
            dp[current][0] += max(dp[next][0], dp[next][1]);            
        }
    }
}

int main() {

    cin >> N;
    for(int i=1; i<=N; i++) cin >> villeage[i];

    for(int i=0; i<N - 1; i++) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }


    dp.resize(MAXNODE, vector<int>(2, 0));   
    for(int i=1; i<=N; i++) {
        dp[i][1] = villeage[i];
        dp[i][0] = 0;
    } 

    dfs(1, 0);
    cout << max(dp[1][0], dp[1][1]);
}