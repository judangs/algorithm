#include <iostream>
#include <unordered_map>

using namespace std;

int N, S;
int arr[41];
unordered_map<int, int> counts;
long long answer = 0;

void add(int d, int sum) {
    if(d == N/2) {
        counts[sum]++;
        return;
    }
    
    add(d + 1, sum);
    add(d + 1, sum + arr[d]);
}

void sub(int d, int sum) {
    if(d == N) {
        answer += counts[S - sum];
        return;
    }
    
    sub(d + 1, sum);
    sub(d + 1, sum + arr[d]);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> S;
    
    for(int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    
    add(0, 0);
    sub(N/2, 0);
    
    if(S == 0) answer--;
    cout << answer << endl;
}