#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int inf = 1e9;
int N, K;
vector<int> energy;

int charge() {
    int sub = energy.front(), ret = -inf;
    for(int idx=1; idx<N; idx++) {
        int now = (energy[idx] - idx * K);
        ret = max(ret, now - sub);
        sub = min(sub, now);
    }

    return ret;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K;
    energy.resize(N);
    for(auto & a: energy) cin >> a;

    int answer = charge();
    reverse(energy.begin(), energy.end());
    answer = max(answer, charge());
    
    cout << answer << endl;
    

}