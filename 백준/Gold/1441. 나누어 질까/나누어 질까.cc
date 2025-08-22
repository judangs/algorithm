#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
typedef long long ll;

int N, L, R;
ll answer = 0ll;

ll calculate(int now) {
    int count = (R / now - (L - 1) / now);
    return count;
}


void dfs(int depth, int ptr, ll now, vector<ll> & arr) {
    
    if(0 < depth && depth % 2 == 1) answer += calculate(now);
    if(0 < depth && depth % 2 == 0) answer -= calculate(now);

    if(depth == N) return;

    for(int idx=ptr; idx<N; idx++) {
        ll next = now * arr[idx] / gcd(now, arr[idx]);
        if(next <= R)
            dfs(depth + 1, idx + 1, next, arr);
    }
}

int main() {

    cin >> N >> L >> R;
    vector<ll> arr(N);
    for(auto & num: arr) cin >> num;

    dfs(0, 0, 1ll, arr);
    cout << answer << endl;
}