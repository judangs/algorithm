#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1e9;
int d, n, m;

int is_valid(int distance, vector<int> & island) {
    int now = 0, ret = 0;
    for(int i=0; i<=n; i++) {
        if(island[i] - now < distance) {
            ret++;
            continue;
        }
        now = island[i];
    }

    return ret;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> d >> n >> m;
    vector<int> island(n + 1);
    for(int i=0; i<n; i++) cin >> island[i];
    island[n] = d;

    sort(island.begin(), island.end());
    int lo = 1, hi = 1e9, answer = 0;
    while(lo + 1 <  hi) {
        int mid = (lo + hi) >> 1;
        if(is_valid(mid, island) <= m) {
            lo = mid, answer = max(answer, mid);
        }
        else
            hi = mid;
    }
    
    if(is_valid(hi, island) == m) answer = max(answer, hi);

    cout << answer;
}