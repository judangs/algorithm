#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int N;
ll B, C, A;
ll one, two, three;

ll greedy(vector<ll> & factory) {

    int left = 0;
    ll answer = 0ll;
    while(left + 2 < N) {
        
        while(left < N && factory[left] == 0)
            left++;

        int right = (left + 2), middle = (left + right) / 2;
        if(factory[middle] > factory[right]) {
            ll count = min(factory[left], factory[middle] - factory[right]);
            factory[left] -= count, factory[middle] -= count;
            answer += two * count;
        }

        ll count = min({ factory[left], factory[middle], factory[right] });
        factory[left] -= count, factory[middle] -= count, factory[right] -= count;
        answer += three * count;

        if(factory[left] == 0) left++;
        else if(factory[middle] == 0) {
            answer += one * factory[left];
            left = middle + 1;
        }
        else if(factory[right] == 0) {
            ll mincount = min(factory[left], factory[middle]);
            factory[left] -= mincount, factory[middle] -= mincount;
            answer += two * mincount + one * max(factory[left], factory[middle]);
            
            left = right + 1;
        }
    }

    if(left + 1 < N) {
        ll mincount = min(factory[left], factory[left + 1]);
        factory[left] -= mincount, factory[left + 1] -= mincount;
        answer += two * mincount + one * max(factory[left], factory[left + 1]);
    }
    else if(left < N) answer += one * factory[left];

    return answer;
}

int main() {

    vector<ll> factory;

    cin >> N >> B >> C;

    one = B;
    two = (2*B <= (B + C) ? 2*B : (B + C));
    three = (3*B <= (B + 2*C) ? 3*B: (B + 2*C));

    for(int idx=0; idx<N; idx++) {
        cin >> A;
        factory.push_back(A);
    }

    cout << greedy(factory);

}