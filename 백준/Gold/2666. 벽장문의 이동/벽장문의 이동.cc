#include <iostream>
#include <cmath>
#include <algorithm>

#define INF 1e9

using namespace std;

int N, M;
int use[21];

int move(int state, int idx) {

    if(idx == M) return 0;

    int ret = INF;
    for(int i=1; i <= N; i++)
        if(!((1 << i) & state)) {
            int nstate = state | (1 << i);
            ret = min(ret, move(nstate ^ (1 << use[idx]), idx + 1) + abs(use[idx] - i));
            break;
        }

    for(int i=N; i >= 1; i--)
        if(!((1 << i) & state)) {
            int nstate = state | (1 << i);
            ret = min(ret, move(nstate ^ (1 << use[idx]), idx + 1) + abs(use[idx] - i));
            break;
        }

    return ret;    

}

int main() {

    cin >> N;
    ++N;
    
    int state = ((1 << (N + 1)) - 1);
    for(int i=0; i<2; i++) {
        int door; cin >> door;
        state ^= (1 << door);
    }

    cin >> M;
    for(int i=0; i<M; i++) cin >> use[i];

    int answer = move(state, 0);
    cout << (answer != INF ? answer : 0) << endl;

}