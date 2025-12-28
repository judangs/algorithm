#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int t;

int main() {

    cin >> t;
    while(t--) {
        int n; cin >> n;
        
        vector<int> even, odd;
        for(int i = 0; i < n; i++) {
            int a; cin >> a;
            if(a % 2 == 0) even.push_back(a);
            else
                odd.push_back(a);
        }

        sort(even.rbegin(), even.rend());
        sort(odd.rbegin(), odd.rend());

        vector<ll> presum(even.size(), 0ll);
        if(!even.empty()) {
            presum.front() = even.front();
            for(int i = 1; i < even.size(); i++)
                presum[i] = presum[i - 1] + even[i];
        }

        ll answer = 0;
        for(int k = 1; k <= n; k++) {
            
            if(odd.empty()) 
                answer = 0;
            else if(even.empty()) {
                if(k % 2 == 0) answer = 0;
                else
                    answer = odd.front();
            }
            else {
                if(k == n && odd.size() % 2 == 0)
                    answer = 0;
                else {

                    answer = odd.front();
                    if(1 <= k - 1 && k - 1 <= even.size()) {
                        answer += presum[k - 1 - 1];
                    }
                    else {
                        if(k != 1) {
                            answer += presum.back();
                            if((k - (even.size() + 1)) % 2 != 0)
                                answer -= even.back();                            
                        }
                    }
                }
            }

            cout << answer << " ";
        }
        cout << "\n";

    }

}
