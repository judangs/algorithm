#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

int N, M;
vector<int> group[100001];


bitset<100001> init(bitset<100001> last) {

    last.flip();
    for(int i=M; i>=1; i--) {
        bool healthy = false;
        for(int person: group[i])
            if(last[person]) healthy = true;

        if(healthy) {
            for(int person: group[i])
                last[person] = 1;
        }
    }

    last.flip();
    return last;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=1; i<=M; i++) {
        int k; cin >> k;
        group[i].resize(k);
        for(auto & person: group[i]) cin >> person;
    }

    bitset<100001> end;
    for(int i=1; i<=N; i++) {
        int state; cin >> state;
        end[i] = state;
    }

    auto state = init(end);
    auto now = state;

    for(int i=1; i<=M; i++) {
        bool contagious = false;
        for(int person: group[i]) {
            if(now[person])
                contagious = true;
        }

        if(contagious) {
            for(int person: group[i])
                now[person] = 1;
        }
    }

    bool tracing = true;
    for(int i=1; i<=N; i++)
        if(now[i] != end[i])
            tracing = false;

    if(tracing) {
        cout << "YES" << endl;
        for(int i=1; i<=N; i++)
            cout << state[i] << " ";
    }
    else {
        cout << "NO" << endl;
    }
    

}