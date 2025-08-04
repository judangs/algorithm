#include <iostream>
#include <map>

using namespace std;

int N;
int solved[100000];

bool valid(int time) {

    map<int, int> count;
    for(int i=0; i<N; i++) {
        int slot = (solved[i] - 1) / time;
        count[slot]++;
    }

    int need = 1;
    for(auto iter = count.begin(); iter != count.end(); iter++) {
        if(iter->first != 0 && iter->first != 1)
            need += (iter->first - 1) * iter->second;
    }

    return need <= count[0];

}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int i=0; i<N; i++) cin >> solved[i];

    int lo = 1, hi = 1e9;
    while(lo + 1 < hi) {
        int mid = (lo + hi) / 2;
        
        if(valid(mid)) 
            hi = mid;
        else
            lo = mid;
    }

    int answer = valid(lo) ? lo : hi;
    cout << answer << endl;

}