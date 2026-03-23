#include <iostream>
#include <vector>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N;
long long K;
vector<long long> foods;

struct Node {
    int end;
    long long cost;
};
vector<Node> arr;
vector<long long> cache;

long long dp(int depth) {
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
    foods = vector<long long>(N);
    arr = vector<Node>(N);
    cache = vector<long long>(N, -1);
    for(auto & food: foods) cin >> food;

    long long sum = 0ll;
    for(int left = 0, right = 0; left < N; left++) {
        while(right < N && sum < K) {
            sum += foods[right++];
        }

        if(K <= sum) arr[left] = { right - 1, sum - K };
        else
            arr[left] = { N - 1, 0 };
        
        sum -= foods[left];
    }

    int ans = dp(0);
    cout << ans << "\n";

}