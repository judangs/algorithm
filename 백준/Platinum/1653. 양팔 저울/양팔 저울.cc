#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

int n, k;
bool weight[10];

map<int, vector<int>> equals;
set<ll> constant;


bool valid(int state) {

    int count[10] = {0, };

    while(0 < state) {
        if(state % 10 == 0) {
            state /= 10; continue;
        }
        if(!weight[state % 10]) return false;
        if(0 < count[state % 10]) return false;
        count[state % 10]++;
        state /= 10;
    }
    return true;
}

int convert(int state) {
    
    int ret = 0;
    for(int distance=1; distance <= 5 && 0 < state; distance++, state /= 10) {
        ret += distance * (state % 10);
    }
    return ret;
}

ll mask(int state, bool rev) {
    string masking = "";
    while(0 < state) {
        masking = char('0' + (state % 10)) + masking;
        state /= 10;
    }
    

    if(rev) {
        reverse(masking.begin(), masking.end());
        masking += string(5 - masking.size(), '0');
    }

    return stoll(masking);
}

bool duplicate(int lstate, int rstate) {
    
    bool visit[10] = {false, };
    for(; 0 < lstate; lstate /= 10)
        visit[lstate % 10] = true;

    for(; 0 < rstate; rstate /= 10)
        if(rstate % 10 != 0 && visit[rstate % 10]) return false;
    return true;
        
}


int main() {
    
    cin >> n;
    for(int i=0; i<n; i++) {
        int w; cin >> w;
        weight[w] = true;
    }
    cin >> k;

    for(int state=1; state <=98765; state++) {
        if(valid(state)) {
            equals[convert(state)].push_back(state);
        }
    }
            

    constant.insert(0ll);
    for(auto iter=equals.begin(); iter != equals.end(); ++iter) {
        auto & states = iter->second; int m = states.size();
        for(int i=0; i<m-1; i++) {
            for(int j=i+1; j<m; j++) {
                if(duplicate(states[i], states[j])) {
                    ll forward = mask(states[i], false) * 100000ll + mask(states[j], true);
                    ll backward = mask(states[j], false) * 100000ll + mask(states[i], true);
                    
                    constant.insert(forward);
                    constant.insert(backward);
                }
            }
        }
    }

    ll answer = 0;
    for(auto iter=constant.begin(); iter != constant.end() && 0 < k + 1; iter++, k--) 
        answer = *iter;

    cout << answer << endl;

}