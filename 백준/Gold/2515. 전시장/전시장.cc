#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL);

using namespace std;

int N, S;
struct Painting {
    int height;
    int cost;
};
vector<Painting> paints;
vector<int> dp(300001, -1);

int display(int depth) {
    if(depth == 0) return 0;
    if(dp[depth] != -1) return dp[depth];

    auto & ret = dp[depth];
    ret = display(depth - 1);
    
    int maxPrevHeight = paints[depth].height - S; 
    
    auto iter = upper_bound(paints.begin(), paints.begin() + depth, maxPrevHeight, 
        [](int v, const Painting & paint) {
            return v < paint.height;
        });
    
    if(iter != paints.begin()) {
        --iter;
        int prevIdx = iter - paints.begin();
        ret = max(ret, display(prevIdx) + paints[depth].cost);
    } else {
        ret = max(ret, paints[depth].cost);
    }

    return ret;
}

int main() {

    fastio;
    cin >> N >> S;
    paints = vector<Painting>(N + 1);
    for(int i = 1; i <= N; i++) cin >> paints[i].height >> paints[i].cost;

    sort(paints.begin(), paints.end(), [](const Painting & a, const Painting & b) {
       if(a.height == b.height) return a.cost > b.cost;
       return a.height < b.height;
    });

    int answer = display(N);
    cout << answer << endl;

}