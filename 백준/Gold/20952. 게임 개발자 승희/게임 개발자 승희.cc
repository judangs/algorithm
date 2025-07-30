#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;

const ll mod = 1e9 + 7;
int N, M;

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    vector<ll> A(N);
    vector<vector<pair<int, ll>>> group(7);
    for(int i=0; i<N; i++) {
        cin >> A[i];
        group[A[i] % 7].push_back({i, A[i]});
    }

    int alive = N;

    vector<bool> visit(7, true);
    ll sum = 0ll;
    for(int i=0; i<M; i++) {
        ll B; cin >> B;
        sum += B; 
        int need = (7 - (sum % 7)) % 7;

        if(alive == group[need].size()) {
            sum -= B;
            continue;
        }
        else {
            if(visit[need]) {
                alive -= group[need].size();
                visit[need] = false;
            }
        }
    }

    vector<pair<int, ll>> answer;
    for(int i=0; i<7; i++) {
        if(visit[i])
            for(auto pairs: group[i])
                answer.push_back({pairs.first, (pairs.second + sum) % mod});
    }

    sort(answer.begin(), answer.end(), [](pil & l, pil & r) {
        return l.first < r.first;
    });

    cout << answer.size() << "\n";
    for(auto ans: answer)
        cout << ans.second << " ";

}