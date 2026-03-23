#include <iostream>
#include <vector>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N, K;
vector<int> foods;

struct Node {
    int end;
    int cost;
};
vector<Node> arr;
vector<int> cache;

int dp(int depth) {
    if(depth == N) return 0;
    
    auto & ret = cache[depth];
    if(ret != -1) return ret;
    
    ret = 0;
    ret = max(ret, dp(depth + 1));
    ret = max(ret, dp(arr[depth].end + 1) + arr[depth].cost);
    return ret;
}

int main() {

    fastio;
    cin >> N >> K;
    foods = vector<int>(N);
    arr = vector<Node>(N);
    cache = vector<int>(N, -1);
    for(auto & food: foods) cin >> food;

    for(int i = 0; i < N; i++) {
        int cost = 0, j;
        for(j = i; j < N; j++) {
            cost += foods[j];
            if(K <= cost) break;
        }
        arr[i] = { min(N - 1, j), (0 < cost - K ? cost - K : 0)};
    }

    int ans = dp(0);
    cout << ans << "\n";

}