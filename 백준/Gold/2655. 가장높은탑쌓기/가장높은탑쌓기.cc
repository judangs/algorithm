#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1e9;
int N;

struct Stone {
    int id, extend, height, weight;

    bool operator<(const Stone & o) const {
        return extend < o.extend;
    }
};

vector<int> dp(101, 0);


int main() {
    
    cin >> N;
    vector<Stone> stones(N + 1);
    stones[0] = {0, 0, 0, 0};
    for(int idx=1; idx<=N; idx++) {
        int e, h, w; cin >> e >> h >> w;
        stones[idx] = {idx, e, h, w};
    }

    sort(stones.begin(), stones.end());

    dp[0] = 0;
    for(int i=1; i<=N; i++) {

        dp[i] = stones[i].height;

        for(int j=0; j<i; j++) {
            if(stones[i].extend > stones[j].extend && stones[i].weight > stones[j].weight) {
                dp[i] = max(dp[i], dp[j] + stones[i].height);
            }
        }
    }

    int maxh = *max_element(dp.begin(), dp.end());

    vector<int> answer;
    for(int idx=N; 1 <= idx; idx--) {
        if(dp[idx] == maxh) {
            answer.push_back(stones[idx].id);
            maxh -= stones[idx].height;
        }
    }
    
    reverse(answer.begin(), answer.end());
    cout << answer.size() << endl;
    for(auto ans: answer) cout << ans << endl;

}