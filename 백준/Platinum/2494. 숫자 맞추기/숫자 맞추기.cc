#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <memory.h>

#define INF 1e9

using namespace std;

int N;
vector<int> init, target;
vector<int> answer;

vector<vector<int>> cache(10001, vector<int>(10, INF));

int turn(int nasa, int spin) {
    if(nasa == N) {
        return 0;
    }
    if(cache[nasa][spin % 10] != INF) return cache[nasa][spin % 10];
    
    int & ret = cache[nasa][spin % 10];

    int now = (init[nasa] + spin) % 10;
    int l = (target[nasa] - now + 10) % 10;
    int r = (now - target[nasa] + 10) % 10;

    ret = min(ret, turn(nasa + 1, spin + l) + l);
    ret = min(ret, turn(nasa + 1, spin) + r);

    return ret;
}

void trace(int nasa, int spin) {
    if(nasa == N) return;
    
    int now = (init[nasa] + spin) % 10;
    int l = (target[nasa] - now + 10) % 10;
    int r = (now - target[nasa] + 10) % 10;
    
    if(cache[nasa][spin % 10] == turn(nasa + 1, spin + l) + l) {
        answer[nasa] = l;
        trace(nasa + 1, spin + l);
    }
    else if(cache[nasa][spin % 10] == turn(nasa + 1, spin) + r) {
        answer[nasa] = -r;
        trace(nasa + 1, spin);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    answer.resize(N);

    string num;
    cin >> num; 
    for(int i=0; i<N; i++) init.push_back(num[i] - '0');
    cin >> num; 
    for(int i=0; i<N; i++) target.push_back(num[i] - '0');

    int count = turn(0, 0);
    cout << count << "\n";
    
    trace(0, 0);
    
    for(int nasa=0; nasa<N; nasa++) {
        if(answer[nasa] != 0) {
            cout << (nasa + 1) << " " << answer[nasa] << "\n";
        }
    }

    return 0;
}