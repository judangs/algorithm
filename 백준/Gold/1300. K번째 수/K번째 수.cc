#include <iostream>
#include <algorithm>

using namespace std;

long long N, K;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> N >> K;

    long long left = 1, right = K;
    while(left + 1 <= right) {
        long long middle = (left + right) / 2;
        
        long long lower = 0;
        for(long long line=1; line<=N; line++) {
            lower += min(middle / line, N);
        }

        if(lower < K) {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }
    
    cout << right;
}