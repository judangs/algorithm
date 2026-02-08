#include <iostream>
#include <numeric>

using namespace std;

int main() {

    int n, m;
    cin >> n >> m;
    int ans = (m - gcd(n, m));
    cout << ans << endl;

}