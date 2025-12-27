#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

const int inf = 1e9;
int N;
string A, B;

int main() {

    fastio;
    cin >> N;
    cin >> A >> B;
    A = ' ' + A; B = ' ' + B;
    vector<long long> pref(2 * N + 1, 0);
    for(int i = 1; i <= 2 * N; i++) pref[i] = pref[i - 1] + (A[i] == 'R' ? 1 : -1) - (B[i] == 'R' ? 1 : -1);
    
    long long psum = 0ll, msum = 0ll;
    for(int i = 1; i < 2 * N; i++) {
        if(pref[i] < 1) msum += (2 - pref[i]) / 2;
        if(pref[i] > -1) psum += (2 + pref[i]) / 2;
    }

    long long answer = min(psum, msum);
    cout << answer << endl;
    

}

