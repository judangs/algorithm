#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, K;

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        cin >> N >> K;

        vector<int> candy(N);

        int value;
        for(int i=0; i<N; i++) {
            cin >> value;
            candy[i] = value;          
        }

        sort(candy.begin(), candy.end());

        int result = INT32_MAX;
        int start = 0;
        int end = start + K - 1;
        while(end < N) {
            result = min(result, candy[end] - candy[start]);
            start++;
            end++;
        }

        cout << "#" << k << " " << result << endl;
    }
}

