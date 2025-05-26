#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int N, A;

ll solve_two_pointer(vector<ll> & factory) {
    
    int left = 0;
    ll answer = 0ll;
    while(left < N) {
        
        while(left < N && factory[left] == 0) {
            left++;
        }

        if(left + 2 < N) {
            int right = (left + 2), middle = (left + right) / 2;

            if(factory[middle] > factory[right]) {
                ll count = min(factory[left], factory[middle] - factory[right]);
                factory[left] -= count, factory[middle] -= count;
                answer += (5 * count);
            }


            ll count = min({ factory[left], factory[middle], factory[right] });

            factory[left] -= count, factory[middle] -= count, factory[right] -= count;
            answer += (7 * count);

            if(factory[left] == 0) {
                left++;
            }
            else if(factory[middle] == 0) {
                answer += (3 * factory[left]);
                left = middle + 1;
            }
            else if(factory[right] == 0) {
                
                ll upper = min(factory[left], factory[middle]);
                answer += (5 * upper);
                factory[left] -= upper, factory[middle] -= upper;

                ll lower = max(factory[left], factory[middle]);

                answer += (3 * lower);
                left = right + 1;
            }
        }
        else if(left + 1 < N) {

            int right = left + 1;

            ll upper = min(factory[left], factory[right]);
            answer += (5 * upper);
            factory[left] -= upper, factory[right] -= upper;

            ll lower = max(factory[left], factory[right]);
            answer += (3 * lower);           

            left = right + 1;            
        }
        else if(left < N) {
            answer += 3 * factory[left];
            left++;
        }
    }

    return answer;
}

int main() {

    vector<ll> factory, rfactory;

    cin >> N;
    for(int idx=0; idx<N; idx++) {
        cin >> A;
        factory.push_back(A);
        rfactory.push_back(A);
    }

    reverse(rfactory.begin(), rfactory.end());
    cout << min(solve_two_pointer(factory), solve_two_pointer(rfactory));

}