#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;
typedef long long ll;

int N, M;
struct MST {
    ll mincost, maxcost;
}mst;

int main() {

    cin >> N;
    M = N * (N - 1) / 2;
    vector<int> tags(M + 1);
    for(int i=1; i<=M; i++) cin >> tags[i];
    
    sort(tags.begin() + 1, tags.end());

    mst.mincost = accumulate(tags.begin() + 1, tags.begin() + N, 0ll);
    for(int k=1; k<N; k++) {
        mst.maxcost += tags[k * (k - 1) / 2 + 1];
    }

    cout << mst.mincost << " " << mst.maxcost;

}