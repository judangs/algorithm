#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
ll N, M;

int play(int turn, ll l, ll r) {
    if(l < r) swap(l, r);
    if(l % r == 0) return turn;
    if(l >= 2*r) return turn;
    return play(turn ^ 1, l - r, r);
}

int main() {

    cin >> N >> M;
    if(play(0, N, M) % 2 == 0) cout << "win" << endl;
    else cout << "lose" << endl;
}