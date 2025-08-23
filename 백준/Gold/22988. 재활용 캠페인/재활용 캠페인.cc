#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int N;
ll X;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> X;
    vector<ll> items(N);
    for(auto & item: items) cin >> item;

    sort(items.begin(), items.end());

    int answer = 0, end = N - 1;
    for(; end>=0 && items[end] >= X; end--) answer++;

    ll half = (X + 1) / 2;
    int left= 0, right = end, extra = 0;
    while(left <= right) {
        
        if(left == right) {
            extra++;
            break;
        }

        if(half <= items[left] + items[right]) {
            answer++, left++, right--;
        }
        else {
            left++;
            extra++;
        }
    }

    answer += extra / 3;
    cout << answer << endl;

}