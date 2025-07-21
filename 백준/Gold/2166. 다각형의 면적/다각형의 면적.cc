#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int N;

struct Pos {
    ll x, y;
};
vector<Pos> lines;

ll ccw(Pos & a, Pos & b) {

    Pos origin = {0, 0};

    ll result = (origin.x*a.y + a.x*b.y + b.x*origin.y) - (a.x*origin.y + b.x*a.y + origin.x*b.y);
    return result;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    
    cin >> N;
    lines.resize(N + 1);
    for(int i=0; i<N; i++) {
        int x, y; cin >> x >> y;
        lines[i] = {x, y};
    }

    lines[N] = {lines[0].x, lines[0].y};

    ll answer = 0ll;
    for(int i=0; i<N; i++) answer += ccw(lines[i], lines[i + 1]);

    cout << fixed;
    cout.precision(1);
    cout << (abs(answer) / 2.0) << endl;

}