#include <iostream>
#include <algorithm>

#define INF 1e9

using namespace std;

int N, M;
int arr[200001];

int prefix[200001], suffix[200001];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for(int i=1; i<=N; i++) cin >> arr[i];

    prefix[1] = arr[1];
    for(int i=2; i<=N; i++) prefix[i] = min(arr[i], prefix[i - 1]);

    suffix[N] = arr[N];
    for(int i=N-1; 1<=i; i--) suffix[i] = max(arr[i], suffix[i + 1]);

    int answer = -INF;
    for(int erase=0; erase<=M; erase++) {
        int sum = suffix[N - (M - erase)] - prefix[1 + erase];    
        answer = max(answer, sum);
    }

    cout << answer << endl;
    
}