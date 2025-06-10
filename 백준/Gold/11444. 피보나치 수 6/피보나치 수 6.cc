#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;
typedef long long ll;
typedef vector<vector<ll>> matrix;

ll N;

matrix operator*(const matrix & l, const matrix & r) {
    matrix multiply(2, vector<ll>(2, 0ll));
    for(int i=0; i<2; i++) {
        for(int j=0; j<2; j++) {
            for(int k=0; k<2; k++) {
                multiply[i][j] += (l[i][k] * r[k][j]) % MOD;
            }

            multiply[i][j] %= MOD;
        }
    }

    return multiply;
}

matrix pow(matrix & a, ll b) {
    if(b == 0) {
        matrix identity(2, vector<ll>(2, 0ll));
        identity[0][0] = 1, identity[1][1] = 1;
        return identity;
    }

    if(b % 2 == 1) return a * pow(a, b - 1);
    
    matrix aa = a * a;
    return pow(aa, b / 2);
}

int main() {

    cin >> N;

    matrix init = {{1, 1}, {1, 0}};
    matrix answer = pow(init, N);

    cout << answer[1][0];
    
}

