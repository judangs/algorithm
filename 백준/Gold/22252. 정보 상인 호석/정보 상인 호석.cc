#include <iostream>
#include <vector>
#include <queue>
#include <map>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int Q;

int main() {

    fastio;
    cin >> Q;

    map<string, priority_queue<int, vector<int>, less<int>>> mpq;

    long long answer= 0ll;
    while(Q--) {
        int opt, k; string name;
        cin >> opt >> name >> k;
        if(opt == 1) {
            while(k--) {
                int C; cin >> C;
                mpq[name].push(C);
            }
        }
        if(opt == 2) {
            if(mpq.find(name) != mpq.end()) {
                while(0 < k && !mpq[name].empty()) {
                    answer += mpq[name].top();
                    mpq[name].pop();
                    k--;
                }
            }
        }
    }

    cout << answer << endl;


}