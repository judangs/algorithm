#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, K;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    for(int t=1; t<=T; t++) {
        
        cin >> N >> K;
        vector<int> stock(N);
        for(int day=0; day<N; day++) cin >> stock[day];

        vector<int> lis; lis.push_back(-1);
        for(int day=0; day<N; day++) {
            if(lis.back() < stock[day])
                lis.push_back(stock[day]);
            else {
                auto iter = lower_bound(lis.begin(), lis.end(), stock[day]);
                *iter = stock[day];
            }
        }

        int answer = (K <= (lis.size() - 1) ? 1 : 0);
        cout << "Case #" << t << endl;
        cout << answer << endl;

    }
    
}