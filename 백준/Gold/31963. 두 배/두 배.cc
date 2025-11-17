#include <iostream>
#include <vector>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL);

using namespace std;

int N;
vector<long long> arr;

int main() {
    fastio;
    cin >> N;
    arr = vector<long long>(N);
    for(auto & A: arr) cin >> A;

    int answer = 0;
    for(int i = 1; i < N; i++) {
        if(arr[i - 1] > arr[i]) {
            int p = 0;
            long long current = arr[i];
            
            while(current < arr[i - 1]) {
                current *= 2;
                p++;
            }
            
            arr[i] = current;
            answer += p;
        }
    }

    cout << answer << '\n';
    
}