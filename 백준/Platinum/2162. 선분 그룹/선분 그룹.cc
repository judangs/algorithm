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
struct Line {
    Pos start, end;
    
    Line(int sx, int sy, int ex, int ey) {
        start = {sx, sy}, end = {ex, ey};
    }
};
vector<Line> lines;


int find(int now, vector<int> & parent) {
    if(parent[now] < 0) return now;
    return (parent[now] = find(parent[now], parent));
}

void merge(int a, int b, vector<int> & parent) {
    a = find(a, parent), b = find(b, parent);
    if(a == b) return;
    if(a > b) swap(a, b);
    parent[a] += parent[b];
    parent[b] = a;
}

int ccw(Pos a, Pos b, Pos c) {
    ll result = (a.x*b.y + b.x*c.y + c.x*a.y) - (b.x*a.y + c.x*b.y + a.x*c.y);
    if(result > 0) return 1;
    if(result < 0) return -1;
    return 0;
}

bool is_cross(Line & a, Line & b) {
    
    int r1 = ccw(a.start, a.end, b.start) * ccw(a.start, a.end, b.end);
    int r2 = ccw(b.start, b.end, a.start) * ccw(b.start, b.end, a.end);

    if(r1 == 0 && r2 == 0) {
        if(min(a.start.x, a.end.x) <= max(b.start.x, b.end.x) && min(b.start.x, b.end.x) <= max(a.start.x, a.end.x) &&
            min(a.start.y, a.end.y) <= max(b.start.y, b.end.y) && min(b.start.y, b.end.y) <= max(a.start.y, a.end.y))
                return true;
    }
    else if(r1 <= 0 && r2 <= 0) return true;
    return false;
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    
    cin >> N;
    vector<int> parent(N, -1);

    for(int i=0; i<N; i++) {
        int sx, sy, ex, ey; cin >> sx >> sy >> ex >> ey;
        lines.push_back({sx, sy, ex, ey});
    }

    for(int i=0; i<N-1; i++) {
        for(int j=i+1; j<N; j++) {
            if(is_cross(lines[i], lines[j]))
                merge(i, j, parent);
        }
    }

    int answer = 0, count = 0;
    for(int i=0; i<N; i++) {
        if(parent[i] < 0) {
            answer++;
            count = max(count, abs(parent[i]));
        }
    }

    cout << answer << endl;
    cout << count << endl;

}