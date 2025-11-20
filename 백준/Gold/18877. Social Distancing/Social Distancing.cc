#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL);

using namespace std;
typedef long long ll;

int N, M;
struct Area {
    ll left;
    ll right;
};
vector<Area> areas;

bool valid(ll distance) {

    int count = 1 , ptr = 0;
    ll now = areas.front().left;

    while(count < N && ptr < M) {
        ll next = now + distance;

        if (next <= areas[ptr].right) {
            now = max(next, areas[ptr].left);
            count++;
        } else {
            ptr++;
        }
    }

    return (count >= N);

}

int main() {

    fastio;
    cin >> N >> M;
    
    areas = vector<Area>(M);
    for(auto & [left, right]: areas) cin >> left >> right;

    sort(areas.begin(), areas.end(), [](auto & l, auto & r) {
        return l.left < r.left;
    });

   ll lo = 1, hi = 1e18 + 1;
   while(lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if(valid(mid)) lo = mid;
        else
            hi = mid;
   }

   ll answer = lo;
   cout << answer << endl;


}