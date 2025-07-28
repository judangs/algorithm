#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
typedef long long ll;

int N;

struct Pos {
    ll x, y;
};
vector<Pos> lines;


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    lines.resize(N);
    for(int i=0; i<N; i++) {
        int x, y; cin >> x >> y;
        lines[i] = {x, y};
    }

    sort(lines.begin(), lines.end(), [](Pos & l, Pos & r) {
        if(l.x == r.x) return l.y < r.y;
        return l.x < r.x;
    });
    
    ll answer = 0ll;
    
    ll left = lines.front().x, right = lines.front().y;
    for(int i=1; i<N; i++) {
        if(lines[i].x <= right) right = max(right, lines[i].y);
        else {
            answer += (right - left);
            left = lines[i].x, right = lines[i].y;
        }
    }

    answer += (right - left);

    cout << answer << endl;
}