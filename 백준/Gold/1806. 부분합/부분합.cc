#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, S;
vector<int> arr;

int solve() {
    int answer = 1e9;
    
    int start = 0, end = 0, sum = 0;
    while(start <= end) {
        if(sum >= S) {
            answer = min(answer, end - start);
            sum -= arr[start++];
        }
        else if(end == arr.size()) break;
        else {
            sum += arr[end++];
        }
    }

    if(answer == 1e9) return 0;
    return answer;
}

int main() {
    cin >> N >> S;

    arr.resize(N);

    int num;
    for(int i=0; i<N; i++) {
        cin >> num;
        arr[i] = num;
    }

    cout << solve();
}