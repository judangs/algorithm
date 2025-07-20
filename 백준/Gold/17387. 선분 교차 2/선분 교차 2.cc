#include <iostream>

using namespace std;

struct Coordinate {
    long long x, y;
};

int ccw(Coordinate A, Coordinate B, Coordinate C) {
    long long result = (A.x*B.y + B.x*C.y + C.x*A.y) - (B.x*A.y + C.x*B.y + A.x*C.y);
    if(result > 0) return 1;
    if(result < 0) return -1;
    return 0;
}

int cross(int l, int r) {
    return (l * r);
}

bool is_overlap(Coordinate A, Coordinate B, Coordinate C, Coordinate D) {

    if(min(A.x, B.x) <= max(C.x, D.x) && min(C.x, D.x) <= max(A.x, B.x)
        && min(A.y, B.y) <= max(C.y, D.y) && min(C.y, D.y) <= max(A.y, B.y))
        return true;
    
    return false;

}

int main() {

    Coordinate A, B, C, D;
    cin >> A.x >> A.y; cin >> B.x >> B.y;
    cin >> C.x >> C.y; cin >> D.x >> D.y;

    int r1 = cross(ccw(A, B, C), ccw(A, B, D));
    int r2 = cross(ccw(C, D, A), ccw(C, D, B));

    if(r1 == 0 && r2 == 0) {
        if(is_overlap(A, B, C, D)) cout << "1" << endl;
        else cout << "0" << endl;
    }
    else if(r1 <= 0 && r2 <= 0) cout << "1" << endl;
    else cout << "0" << endl;
    
}