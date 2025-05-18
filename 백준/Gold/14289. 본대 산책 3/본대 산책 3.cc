#include <iostream>
#include <vector>

#define MOD 1000000007

using namespace std;

typedef long long ll;

int n, m, a, b;
int D;


vector<vector<ll>> operator*(const vector<vector<ll>> & l, const vector<vector<ll>> & r) {
    vector<vector<ll>> ret(n, vector<ll>(n));
    for(int i=0; i<n; i++) {
        for(int j=0; j < n; j++) {
            for(int k=0; k<n; k++) {
                ret[i][j] = (ret[i][j] + l[i][k] * r[k][j]) % MOD;
            }
        }
    }

    return ret;
}

vector<vector<ll>> pow(vector<vector<ll>> & matrix, int d) {
    if(d == 0) {
        vector<vector<ll>> identiy(n, vector<ll>(n));
        for(int i=0; i<n; i++) identiy[i][i] = 1;
        return identiy;
    }

    if(d % 2 == 1) return matrix * pow(matrix, d - 1);

    vector<vector<ll>> pmatrix = matrix * matrix;
    return pow(pmatrix, d / 2);
}

int main() {

    cin >> n >> m;
    vector<vector<ll>> adj(n, vector<ll>(n));
    for(int idx=0; idx<m; idx++) {
        cin >> a >> b;
        adj[a - 1][b - 1] = 1;
        adj[b - 1][a - 1] = 1;
    }

    cin >> D;
    vector<vector<ll>> result = pow(adj, D);
    cout << result[0][0] % MOD;
    

}