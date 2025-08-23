#include <iostream>
#include <iomanip>

using namespace std;

double d, s, e;

int main() {

    cin >> d >> s >> e;

    double answer;
    if(s <= d - s - e) 
        answer = (d - s) / d * s / (d - s - e);
    else 
        answer = (s + e) / d;
    cout << fixed << setprecision(6);
    cout << answer << endl;

}