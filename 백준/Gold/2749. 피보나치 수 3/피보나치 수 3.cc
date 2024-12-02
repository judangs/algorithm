#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

vector<ull> arr;

ull N, P;
ull DIV = 1000000;

int main() {
    
    cin >> N;
    P = 100000 * 15;
    
    arr.push_back(0);
    arr.push_back(1);
    
    ull idx = 2;
    while(idx <= P) {
        arr.push_back((arr[idx - 1] + arr[idx - 2]) % DIV);
        idx += 1;
    }
    
    cout << arr[N % P];
}