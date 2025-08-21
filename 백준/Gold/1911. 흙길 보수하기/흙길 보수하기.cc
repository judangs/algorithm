#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, L;
struct Pool {
    int start, end;

    bool operator<(const Pool & o) const {
        return start < o.start;
    }
};
vector<Pool> pools;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> L;
    for(int i=0; i<N; i++) {
        int s, e; cin >> s >> e;
        pools.push_back({s, e});
    }

    sort(pools.begin(), pools.end());
    
    int answer = 0, plank = -1;
    for(auto pool: pools) {
        while(plank < pool.end) {
            if(plank < pool.start) plank = pool.start;
            plank += L;
            answer++;            
        }
    }

    cout << answer << endl;


}