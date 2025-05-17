#include <iostream>
#include <vector>

#define MOD 1000

using namespace std;

typedef vector<vector<long long>> matrix;


int N, A;
long long B;


matrix operator*(const matrix & l, const matrix & r) {

    matrix ret(N, vector<long long>(N, 0));
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            for(int k=0; k<N; k++) {
                ret[i][j] += (l[i][k] * r[k][j]) % MOD;
            }

            ret[i][j] %= MOD;
        }
    }

    return ret;
}

matrix pow(matrix & a, long long b) {
    if(b == 0) {
        matrix idmatrix(N, vector<long long>(N, 0));
        for(int i=0; i<N; i++) 
            idmatrix[i][i] = 1;
        return idmatrix;
    }
    if(b % 2 == 1) return a * pow(a, b - 1);

    matrix aa = a * a;
    return pow(aa, b / 2);
}

int main() {

    cin >> N >> B;
    matrix array(N, vector<long long>(N));
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> array[i][j];
        }
    }

    matrix result = pow(array, B);
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cout << result[i][j] % MOD << " ";
        }
        cout << "\n";
    }

    
    
}