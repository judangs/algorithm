#include <iostream>
#include <vector>
#include <algorithm>

#define MAXSET 100000

using namespace std;

int N, K, x;
vector<int> testset;

int check(int score) {
    int count = 0, psum = 0;
    for(auto test: testset) {
        psum += test;
        if(psum >= score) {
            count++;
            psum = 0;
        }
    }

    return count;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K;

    for(int i=0; i<N; i++) {
        cin >> x;
        testset.push_back(x);
    }
    
    int answer = 0;
    int left = 0, right = MAXSET * 20 + 1;
    while(left + 1 < right) {
        int mid = (left + right) / 2;
        
        if(check(mid) >= K) left = mid;
        else right = mid;
    }

    cout << left;
}