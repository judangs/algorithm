#include <iostream>

using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;
int N, M;
string board[2000];

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

ll pow(ll a, int b) {
    if(b == 0) return 1ll;
    if(b % 2 == 1) return (a * pow(a, b - 1)) % mod;
    return (pow((a * a) % mod, b / 2) % mod);
}

bool check(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=0; i<N; i++)
        cin >> board[i];

    int count = 0;
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++) {

            bool random = true;
            for(int dir=0; dir<4; dir++) {
                int ny = i + dy[dir], nx = j + dx[dir];
                if(!check(ny, nx)) continue;
                if(board[i][j] != board[ny][nx])
                    random = false;
            }

            if(random)
                count++;
        }

    ll answer = pow(2ll, count);
    cout << answer << endl;

}