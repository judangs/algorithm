#include <iostream>
#include <vector>

#define MOD 1000003

using namespace std;

typedef long long ll;
typedef vector<vector<ll>> matrix;

int N, S, E;
ll T;


matrix operator*(const matrix & l, const matrix & r) {

    matrix ret(5 * N, vector<ll>(5 * N, 0));
    for(int i=0; i<5*N; i++) {
        for(int j=0; j<5*N; j++) {
            for(int k=0; k<5*N; k++) {
                ret[i][j] = (ret[i][j] + l[i][k] * r[k][j]) % MOD;
            }
        }
    }

    return ret;
}

matrix pow(matrix a, ll b) {
    if(b == 0) {
        matrix identity(5 * N, vector<ll>(5 * N, 0));
        for(int i=0; i<5*N; i++) identity[i][i] = 1;
        return identity;
    }

    if(b % 2 == 1) return a * pow(a, b - 1);
    matrix aa = a * a;
    return pow(aa, b / 2);
}

int main() {

    cin >> N >> S >> E >> T;
    S--, E--;

    matrix adj(5 * N, vector<ll>(5 * N));

    char cost;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            for(int k=0; k<4; k++)
                adj[5 * i + k][5 * i + k + 1] = 1;
                // 각 자리에서 멤도는 경우는 연결되어 있다고 표현, 노드 단위의 이동이 아니므로 그래프 정보 없이도 카운팅

            cin >> cost;
            if(cost == '0') continue;

            int distance = cost - '0';
            int s = 5 * i + (distance - 1), e = 5 * j;
            adj[s][e] = 1;
        }
    }

    matrix result = pow(adj, T);
    cout << result[5*S][5*E];
    

}