#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int N, K;
priority_queue<int, vector<int>, less<int>> pq;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K;
    vector<int> kinder(N);

    for(int i=0; i<N; i++) cin >> kinder[i];
    for(int i=1; i<N; i++) pq.push(kinder[i] - kinder[i - 1]);

    while(K-- - 1 != 0) pq.pop();

    long long answer = 0;;
    while(!pq.empty()) {
        answer += pq.top(); pq.pop();
    }

    cout << answer;
}