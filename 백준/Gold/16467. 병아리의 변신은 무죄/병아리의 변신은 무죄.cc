#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
typedef vector<ll> arrays;
typedef vector<arrays> matrix;

int T, K, N;
const int MOD = 1e8 + 7;

matrix operator*(const matrix & l, const matrix & r) {
    matrix ret(K, arrays(K));
    for(int i=0; i<K; i++) {
        for(int j=0; j<K; j++) {
            for(int k=0; k<K; k++) {
                ret[i][j] = (ret[i][j] + l[i][k] * r[k][j]) % MOD;
            }
        }
    }

    return ret;
}

matrix pow(matrix & a, ll b) {
    if(b == 0) {
        matrix identity(K, arrays(K));
        for(int i=0; i<K; i++) identity[i][i] = 1;
        return identity;
    }

    if(b % 2 == 1) return a * pow(a, b - 1);
    matrix aa = a * a;
    return pow(aa, b / 2);
}

int main() {

    cin >> T;
    while(T--) {
        cin >> K >> N;
        K++;

        matrix init(K, arrays(K));
        init[0][0]++, init[0][K - 1]++;
        for(int i=1; i<K; i++) init[i][i - 1] = 1;

        matrix answer = pow(init, N);
        cout << answer[0][0] << "\n"; 
    }
}