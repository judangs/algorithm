#include <iostream>

using namespace std;

int N;

int main() {
    
    cin >> N;
    if(N % 2 == 0) cout << "Duck";
    else
        cout << "Goose";
}