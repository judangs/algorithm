#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;

ll N, A = 1;
vector<ll> num(10, 0);


void sequence(ll current, int pos) {
    while(current > 0) {
        num[current % 10] += pos;
        current /= 10;
    }
}

int main() {

    cin >> N;

    int p = 0;
    while(0 < N && A <= N) {
        while(A <= N && A % 10 != 0) sequence(A++, pow(10, p));
        while(A <= N && N % 10 != 9) sequence(N--, pow(10, p));

        if(A > N) break;

        ll usage = (N / 10 - A / 10 + 1) * pow(10, p);
        for(int idx=0; idx<=9; idx++) {
            num[idx] += usage;
        }

        A /= 10, N /= 10;   
        p++;
    }


    for(auto use: num) {
        cout << use << " ";
    }

}