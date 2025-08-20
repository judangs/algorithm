#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<int> arr(N + 1);
    for(int i=1; i<=N; i++) cin >> arr[i];

    vector<int> forward(N + 1, 0);
    vector<int> backward(N + 2, 0);
    for(int i=1; i<=N; i++) forward[i] = forward[i - 1] + arr[i];
    for(int i=N; i>=1; i--) backward[i] = backward[i + 1] + arr[i];

    int answer = 0;
    for(int middle=2; middle < N; middle++) {
        int honey = (forward[N] - arr[1] - arr[middle]) + (forward[N] - forward[middle]);
        answer = max(answer, honey);
    }
    for(int middle=2; middle<N; middle++) {
        int honey = (backward[1] - arr[N] - arr[middle]) + (backward[1] - backward[middle]);
        answer = max(answer, honey);
    }

    int pivot = max_element(arr.begin() + 2, arr.begin() + N) - arr.begin();
    int honey = forward[pivot] - arr[1] + backward[pivot] - arr[N];
    answer = max(answer, honey);

    cout << answer << endl;
    

}