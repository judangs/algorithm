#include <iostream>
#include <vector>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

const ll inf = 1e18;
int N;

struct Food {
    ll A;
    ll B;
};

int main() {

    fastio;
    cin >> N;

    vector<Food> foods(N + 1);
    for(int i = 1; i <= N; i++) cin >> foods[i].A >> foods[i].B;
    
    sort(foods.begin() + 1, foods.end(), [](const Food & l, const Food & r) {
        return l.B < r.B;
    });

    vector<ll> prefix(N + 1, 0ll);
    for(int i = 1; i <= N; i++) prefix[i] = prefix[i - 1] + foods[i].B;
    vector<ll> suffix(N + 1, inf); suffix[N] = foods[N].A;
    for(int i = N - 1; 0 < i; i--) suffix[i] = min(suffix[i + 1], foods[i].A);

    vector<ll> prefmin(N + 1, 0ll); prefmin[1] = foods[1].A - foods[1].B;
    for(int i = 2; i <= N; i++) prefmin[i] = min(prefmin[i - 1], foods[i].A - foods[i].B);
    
    for(int i = 1; i <= N; i++) {
        ll answer = (i == 1) ? prefix[i - 1] + suffix[i] 
                            : min(prefix[i - 1] + suffix[i], prefix[i] + prefmin[i - 1]);
        cout << answer << "\n";
    }

}