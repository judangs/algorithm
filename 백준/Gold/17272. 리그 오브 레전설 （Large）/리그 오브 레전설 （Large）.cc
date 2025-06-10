#include <iostream>
#include <vector>
#include <cstdlib>

#define MOD 1000000007

using namespace std;
typedef long long ll;
typedef vector<vector<ll>> matrix;

ll N, M;

matrix operator*(const matrix & l, const matrix & r) {
    matrix ret(M, vector<ll>(M, 0));
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            for(int k=0; k<M; k++) {
                ret[i][j] += (l[i][k] * r[k][j]) % MOD;
            }

            ret[i][j] %= MOD;
        }
    }

    return ret;
}

matrix pow(matrix & a, ll b) {
    if(b == 0) {
        matrix ident(M, vector<ll>(M));
        for(int i=0; i<M; i++) ident[i][i] = 1;
        return ident;
    }

    if(b % 2 == 1) return a * pow(a, b - 1);
    
    matrix aa = a * a;
    return pow(aa, b / 2);
}

int main() {

    cin >> N >> M;
    if(N < M) {
        cout << "1";
        exit(0);
    }

    matrix init(M, vector<ll>(M));
    init[0][0] = 1, init[0][M - 1] = 1;
    for(int i=0; i<M; i++) {
        for(int j=0; j<M; j++) {
            if(i - 1 == j) init[i][j] = 1;
        }
    }    

    matrix pmatrix = pow(init, N - M);
    
    ll answer = 0ll;
    for(int i=0; i<M; i++) {
        if(i == 0) answer = (answer + (pmatrix[0][i] * 2) % MOD) % MOD;
        else answer = (answer + pmatrix[0][i]) % MOD;
    }
    
    cout << answer;
}