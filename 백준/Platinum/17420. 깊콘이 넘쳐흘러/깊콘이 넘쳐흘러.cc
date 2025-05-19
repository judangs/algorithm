#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

int N;
vector<pair<ll, ll>> gift;

ll extend_with(ll expired, ll wanted) {
    ll count = (wanted - expired) / 30 + 1;
    if((wanted - expired) % 30 == 0) --count;
    return count;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    
    gift.resize(N);
    for(int idx=0; idx<N; idx++) cin >> gift[idx].first;
    for(int idx=0; idx<N; idx++) cin >> gift[idx].second;

    sort(gift.begin(), gift.end(), [](pll & l, pll & r) {
        if(l.second == r.second) {
            return l.first < r.first;
        }
        return l.second < r.second;
    });

    ll answer = 0ll;

    auto & front = gift.front();
    if(front.first < front.second) {
        ll extend = extend_with(front.first, front.second);
        front.first += 30 * extend;
        answer += extend;
    }

    ll end = front.second, pmax = front.first, cmax = front.first;
    for(int idx=1; idx<gift.size(); idx++) {

        auto & item = gift[idx];
        if(end < item.second) {
            end = item.second;
            pmax = cmax;
        }

        
        if(item.first < item.second) {
            ll extend = extend_with(item.first, item.second);
            item.first += 30 * extend;
            answer += extend;
        }

        if(pmax > item.first) {
            ll extend = extend_with(item.first, pmax);
            item.first += 30 * extend;
            answer += extend;
        }        

        cmax = max(cmax, item.first);

    }

    
    cout << answer;
    
}