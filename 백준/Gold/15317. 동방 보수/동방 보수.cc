#include <iostream>
#include <vector>
#include <algorithm>

#define SORT(v) sort((v).begin(), (v).end())

using namespace std;
typedef long long ll;

int N, M;
ll X, C, S;

vector<ll> repair;
vector<ll> budget;

bool can_support(int num) {

    ll balance = X;
    for(int idx=1; idx<=num; idx++) {
        ll require = budget[M - idx] - repair[num - idx];
        if(require < 0) {
            balance += require;
            if(balance < 0) return false;
        }
    }

    return true;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N >> M >> X;
    for(int i=0; i<N; i++) {
        cin >> C;
        repair.push_back(C);
    }

    int answer = 0;
    for(int i=0; i<M; i++) {
        cin >> S;
        budget.push_back(S);
    }   

    SORT(repair), SORT(budget);

    int left = 0, right = min(M, N);
    while(left + 1 < right) {
        int mid = (left + right) / 2;

        if(can_support(mid)) left = mid;
        else right = mid;
    }

    if(can_support(right)) cout << right;
    else cout << left;
}