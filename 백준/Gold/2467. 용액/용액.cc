#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int N;
vector<int> arr;

pair<int, int> solve() {
    int left = 0, right = N - 1;
    int min_abs = INT32_MAX;

    pair<int, int> answer;
    while(left < right) {
        int current = (arr[left] + arr[right]);
        if(abs(current) < min_abs) {
            min_abs = abs(current);
            answer = {left, right};
        }

        if(current >= 0) right--;
        else left++;
    }

    return answer;
}

int main() {
    cin >> N;
    arr.resize(N);

    for(int i=0; i<N; i++) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    auto answer = solve();
    cout << arr[answer.first] << " " << arr[answer.second];
}