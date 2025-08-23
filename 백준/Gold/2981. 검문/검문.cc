#include <iostream>
#include <numeric>
#include <cmath>

using namespace std;

int N;
int num[100];

int main() {

    ios::sync_with_stdio(false);
    cout.tie(0);

    cin >> N;
    for(int i=0; i<N; i++) cin >> num[i];
    
    int _gcd = num[1] - num[0];
    for(int i=2; i<N; i++) _gcd = gcd(_gcd, abs(num[i] - num[i - 1]));

    for(int mod=2; mod<=_gcd / 2; mod++) 
        if(_gcd % mod == 0) cout << mod << " ";
    cout << _gcd << endl;
    

}