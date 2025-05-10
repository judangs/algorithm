#include <iostream>
#include <queue>
#include <functional>
#include <cstdio>

using namespace std;

int N, A;

priority_queue<int, vector<int>, greater<int>> minpq;
priority_queue<int, vector<int>, less<int>> maxpq;


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> A;

        maxpq.push(A);

        int diff = maxpq.size() - minpq.size();
        while(!maxpq.empty() && diff-- > 1) {
            minpq.push(maxpq.top());
            maxpq.pop();
        }                
    
        while(!maxpq.empty() && !minpq.empty() && maxpq.top() > minpq.top()) {
            minpq.push(maxpq.top());
            maxpq.push(minpq.top());
            maxpq.pop();
            minpq.pop();
        }

        cout << maxpq.top() << "\n";
    }
}