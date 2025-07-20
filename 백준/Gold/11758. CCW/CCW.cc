#include <iostream>

using namespace std;

struct Coordinate {
    int x, y;
};

int main() {

    Coordinate A, B, C;
    cin >> A.x >> A.y;
    cin >> B.x >> B.y;
    cin >> C.x >> C.y;

    int ccw = (A.x*B.y + B.x*C.y + C.x*A.y) - (B.x*A.y + C.x*B.y + A.x*C.y);
    if(ccw > 0) cout << "1" << endl;
    if(ccw == 0) cout << "0" << endl;
    if(ccw < 0) cout << "-1" << endl;
    
    
}