#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;

int N;
string A, B;

long long swap_d(string a, string b) {

    vector<long long> d(2 * N + 1, 0ll);
    int count = 0;
    if(a[1] != 'U') {
        if(a[2 * N] != 'R') {
            swap(a[1], a[2 * N]);
        }
        else {
            for(int i = 2 * N; 0 < i; i--) {
                if(a[i] == 'U') {
                    swap(a[1], a[i]);
                    break;
                }
            }
        }
        count++;
    }
    if(a[2*N] != 'R') {
        for(int i = 1; i <= 2 * N; i++) {
            if(a[i] == 'R') {
                swap(a[i], a[2*N]);
                break;
            }
        }
        count++;
    }
    if(b[1] != 'R') {
        if(b[2*N] != 'U') {
            swap(b[1], b[2*N]);
        }
        else {
            for(int i = 2*N; 0 < i; i--) {
                if(b[i] == 'R') {
                    swap(b[1], b[i]);
                    break;
                }
            }
        }
        count++;
    }
    if(b[2*N] != 'U') {
        for(int i = 1; i <= 2 * N; i++) {
            if(b[i] == 'U') {
                swap(b[i], b[2*N]);
                break;
            }
        }
        count++;
    }

    for(int i = 1; i < 2 * N; i++) d[i] = d[i - 1] + (a[i] == 'U') - (b[i] == 'U');
    long long m = *min_element(d.begin() + 1, d.begin() + 2 * N);
    return (count + (1 - m));
}

int main() {

    fastio;
    cin >> N;
    cin >> A >> B;
    A = ' ' + A; B = ' ' + B;
    long long answer = min(swap_d(A, B), swap_d(B, A));
    cout << answer << endl;

}