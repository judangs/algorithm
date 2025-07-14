#include <iostream>

using namespace std;

int w, h, p, q, t;

int main() {

    cin >> w >> h;
    cin >> p >> q;
    cin >> t;
    
    p = (p + t) % (2 * w), q = (q + t) % (2 * h);
    if(p > w) p = 2 * w - p;
    if(q > h) q = 2 * h - q;

    cout << p << " " << q;
    
}