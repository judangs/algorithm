#include <iostream>

using namespace std;

int N;
int num[51];


bool solved(int d, int a, int b) {
    if(d == N) return true;
    if(a * num[d] + b == num[d + 1]) return solved(d + 1, a, b);
    return false;
}

int main() {

    cin >> N;
    for(int i=1; i<=N; i++) cin >> num[i];

    if(N <= 2) {
        if(N == 2 && num[1] == num[2]) cout << num[N] << endl;
        else cout << "A" << endl;

        return 0;
    }

    int answer = -1, count = 0;
    for(int a=-200; a<=200; a++) {
        for(int b=-20000; b<=20000; b++) {
            if(solved(1, a, b)) {
                answer = a * num[N] + b;
                count++;
            }
        }
    }

    if(0 == count) 
        cout << "B" << endl;
    else
        cout << answer << endl;
    
}