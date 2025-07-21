#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;

struct Item {
    int weight;
    int valuable;
};

vector<Item> items;



int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=1; i<=N; i++) {
        int V, C, K; cin >> V >> C >> K;
        
        int pow = 1;
        while(K > 0) {
            int take = min(K, pow);
            items.push_back({V * take, C * take});
            K -= take, pow *= 2;
        }
    }

    vector<vector<int>> dp(items.size(), vector<int>(M + 1, 0));

    for(int weight=0; weight <= M; weight++)
        if(items.front().weight <= weight)
            dp[0][weight] = items.front().valuable;

    
    for(int idx=1; idx < items.size(); idx++) {
        
        auto & item = items[idx];
        for(int weight=0; weight <= M; weight++) {
            if(0 <= weight - item.weight)
                dp[idx][weight] = max(dp[idx - 1][weight - item.weight] + item.valuable, dp[idx - 1][weight]);
            else
                dp[idx][weight] = max(dp[idx][weight], dp[idx - 1][weight]);
        }
    }

    int answer = dp[items.size() - 1][M];
    cout << answer << endl;

}