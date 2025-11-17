#include <iostream>
#include <vector>
#include <cmath>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL);

using namespace std;

int N;
vector<int> arr;

bool valid(int a, int b) {
    return (a <= b);
}

int main() {

    fastio;
    cin >> N;
    arr = vector<int>(N);
    for(auto & A: arr) cin >> A;

    int answer = 0;
    for(int i = 1; i < N; i++) {
        if(arr[i - 1] > arr[i]) {
            int lo = 1, hi = 30;
            while(lo + 1 < hi) {
                int mid = (lo + hi) / 2;
                if(valid(arr[i - 1], pow(2, mid) * arr[i])) hi = mid;
                else lo = mid;
            }

            int p;
            if(valid(arr[i - 1], pow(2, lo) * arr[i])) p = lo;
            else p = hi;
            arr[i] *= pow(2, p);
            answer += p;
        }
    }

    cout << answer;
    
}