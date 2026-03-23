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

    int left = 0, right = 0, now = 0;
    bool finish = false;
    while(left < N && right < N) {
        if(right == N - 1) {
            if(!finish) {
                now += foods[right];
                finish = true;
            }
            if(K <= now) {
                arr[left] = { right, now - K };
            }
            if(now < K) {
                arr[left] = { right, 0 };
            }

            now -= foods[left++];

            if(left == N - 1)
                break;
        }
        if(right < N - 1) {
            now += foods[right];
            while(K <= now) {
                arr[left] = { right, now - K };
                now -= foods[left++];
            }
            right++;
        }
    }

    arr[N - 1] = { N - 1, (K <= foods[N - 1] ? foods[N - 1] - K : 0) };

    int ans = dp(0);
    cout << ans << "\n";

}