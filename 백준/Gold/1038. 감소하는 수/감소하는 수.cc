#include <iostream>
#include <cmath>
#include <set>
#include <functional>

using namespace std;
typedef long long ll;

const ll inf = 9876543210;

int N;
set<ll> sq;

void backtracking(int depth, ll num, int front) {
    if(num > inf) return;

    sq.insert(num);

    for(int next=front + 1; next<=9; next++) {
        ll nnum = ((ll) pow(10ll, depth + 1)) * (ll) next + num;
        backtracking(depth + 1, nnum, next);
    }
}

int main() {
    
    cin >> N;
    for(int i=0; i<=9; i++) backtracking(0, i, i);

    if(sq.size() <= N) cout << "-1" << endl;
    else {
        auto iter = sq.begin();
        while(N--) iter++;
        cout << *iter << endl;
    }
    
}