#include <iostream>
#include <cstring>

using namespace std;

int main() {

    int X, Y;
    cin >> X >> Y;
    long long answer = stoll(string(X, '1')) + stoll(string(Y, '1'));
    cout << answer << endl;

}