#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;

int N;
ll X, A;

vector<pll> arr;


int main() {
    
    cin >> N;
    arr.resize(N + 1);
    
    ll total = 0ll;
    for(int i=1; i<=N; i++) {
        cin >> X >> A;
        arr[i] = {X, A};
        total += A;
    }
    
    sort(arr.begin() + 1, arr.end(), [](const pll & l, const pll & r) {
        return l.first < r.first;
    });

    ll sum = 0ll;
    int answer;
    for(auto villeage: arr) {
        sum += villeage.second;
        if(sum >= (total + 1) / 2) {
            answer = villeage.first; 
            break;
        }
    }

    cout << answer;
}