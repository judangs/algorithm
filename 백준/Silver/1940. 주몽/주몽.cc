#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, A;
vector<int> arr;

int main() {

    cin >> N >> M;
    for(int i=0; i<N; i++) {
        cin >> A;
        arr.push_back(A);
    }

    sort(arr.begin(), arr.end());
    
    int left = 0, right = arr.size() - 1;

    int answer = 0;
    while(left < right) {

        int sum = arr[left] + arr[right];

        if(sum == M) {
            answer++;
            left++, right--;
        }
        else if(sum > M) {
            right--;
        }
        else {
            left++;
        }
    }

    cout << answer;
}