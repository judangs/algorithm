#include <iostream>
#include <vector>
 
using namespace std;
 
int T;
 
int main() {
 
    cin >> T;
    while(T--) {
        int N; cin >> N;
        vector<int> arr(N);
        for(auto & num: arr) cin >> num;
        
        int answer = 0;
        for(int i = 0; i < N; i++) {
            for(int j = i - 1; 0 <= j; j--) {
                if(arr[j] > arr[i]) {
                    answer++;
                    break;
                }
            }
        }
 
        cout << answer << endl;
    }
 
}
