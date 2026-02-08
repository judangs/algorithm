#include <iostream>
#include <vector>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

bool valid(ll n, ll time, vector<int> & times) {
    ll count = 0;
    for(auto & t: times) 
        count += (time / t) + 1;
    return count >= n;
}

int solve(ll n, ll time, vector<int> & times) {

    ll count = 0;
    for(int i = 0; i < times.size(); i++)
        count += (time - 1) / times[i] + 1;

    int ret = -1;
    for(int i = 0; i < times.size(); i++) {
        if(time % times[i] == 0) {
            count++;
            if(count == n) {
                ret = (i + 1);
            }
        }
    }
    return ret;
}

int main() {

    fastio;

    ll n, m;
    cin >> n >> m;
    vector<int> times(m);
    for(auto & t: times) cin >> t;

    if(n <= m) {
        cout << n << endl;
        return 0;
    }

    ll lo = 0, hi = 30 * n;
    while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(valid(n, mid, times)) hi = mid;
        else lo = mid;
    }

    ll T = hi;
    cout << solve(n, T, times) << endl;
}
