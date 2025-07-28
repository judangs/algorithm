#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1e9

using namespace std;

int n, k;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n >> k;
    vector<int> coin(n);
    for(int i=0; i<n; i++) cin >> coin[i];

    sort(coin.begin(), coin.end());

    vector<int> dp(k + 1, INF);
    dp[0] = 0;
    for(int i=0; i<n; i++) {

        auto value = coin[i];
        for(int amount=value; amount<=k; amount++) {
            if(dp[amount - value] != INF) {
                dp[amount] = min(dp[amount], dp[amount - value] + 1);
            }
        }
    }

    int answer = (dp[k] != INF ? dp[k] : -1);
    cout << answer << endl;

}