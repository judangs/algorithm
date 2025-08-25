#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>


using namespace std;
typedef long long ll;

int N, M;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    ll lcm = N * M / gcd(N, M);
    vector<int> cycle(N + 1, 0);
    for(int i=1; i<=lcm; i++) {
        if(i % M == 0) continue;
        int now = (i % N == 0) ? N : (i % N);
        cycle[now]++;
    }

    vector<ll> assign(N + 1);
    vector<ll> count(N + 1);
    for(int i=1; i<=N; i++) {
        cin >> assign[i];
        if(cycle[i]) count[i] = (assign[i] + cycle[i] - 1) / cycle[i];
        else count[i] = INT32_MAX;
    }

    int mincycle = *min_element(count.begin() + 1, count.end()) - 1;
    for(int i=1; i<=N; i++) assign[i] -= (mincycle * cycle[i]);

    int answer;
    for(int i=1; i<=lcm; i++) {
        if(i % M == 0) continue;
        int now = (i % N == 0) ? N : (i % N); assign[now]--;
        if(!assign[now]) {
            answer = now;
            break;
        }
    }

    cout << answer << endl;

}