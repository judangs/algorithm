#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<long long> arr;

int binary_search(int left, int right, long long target) {
    while(left + 1 < right) {
        int mid = (left + right) / 2;
        if(0 == target + arr[mid]) return mid;
        else if(0 < target + arr[mid]) right = mid;
        else left = mid;
    }
    
    if(abs(arr[left] + target) < abs(arr[right]) + target)
        return left;
    return right;
}

int main() {
    cin >> N;
    arr.resize(N);
    for(int idx=0; idx<N; idx++) {
        cin >> arr[idx];
    }
    
    sort(arr.begin(), arr.end());
    
    long long maxabs = 1e18;
    vector<long long> answer;
    for(int i=0; i<N - 2; i++) {
        for(int j=i + 1; j<N - 1; j++) {
            int idx = binary_search(j + 1, N - 1, arr[i] + arr[j]);
            
            if(abs(arr[i] + arr[j] + arr[idx]) < maxabs) {
                maxabs = abs(arr[i] + arr[j] + arr[idx]);
                answer = {arr[i], arr[j], arr[idx]};
            }
        }
    }
    
    sort(answer.begin(), answer.end());
    for(auto ans: answer) {
        cout << ans << " ";
    }
}