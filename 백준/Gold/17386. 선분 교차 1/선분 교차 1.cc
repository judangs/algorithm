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

bool cross(int l, int r) {
    return (l * r) < 0;
}

int main() {

    Coordinate A, B, C, D;
    cin >> A.x >> A.y; cin >> B.x >> B.y;
    cin >> C.x >> C.y; cin >> D.x >> D.y;
    
    if(cross(ccw(A, B, C), ccw(A, B, D)))
        if(cross(ccw(C, D, A), ccw(C, D, B))) {
            cout << "1" << endl;
            return 0;
        }
    
    cout << "0" << endl;
    
}