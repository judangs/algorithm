#include <iostream>
#include <vector>
#include <algorithm>
#include <algorithm>

using namespace std;

int N;

int main() {
    cin >> N;
    
    vector<int> arr(N);
    for(int idx=0; idx<N; idx++) {
        cin >> arr[idx];
    }
    
    vector<int> lis;
    vector<int> trace(arr.size());
    lis.push_back(-1);
    for(int idx=0; idx<N; idx++) {
        if(lis.back() < arr[idx]) {
            lis.push_back(arr[idx]);
            trace[idx] = lis.size() - 1;
        }
        else {
            int ptr = lower_bound(lis.begin(), lis.end(), arr[idx]) - lis.begin();
            lis[ptr] = arr[idx];
            trace[idx] = ptr;
        }
    }
    
    int count = lis.size() - 1;
    cout << count << "\n";
    
    vector<int> answer(count);
    for(int idx=trace.size()-1; idx>=0 && count > 0; idx--) {
        if(count == trace[idx]) {
            answer[count - 1] = arr[idx];
            count--;
        }
    }
    
    sort(answer.begin(), answer.end());
    for(int ans: answer) {
        cout << ans << " ";
    }
}