#include <iostream>
#include <vector>

using namespace std;

int N, M, num;
vector<int> arr, prefix;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for(int i=0; i<N; i++) {
        cin >> num;
        arr.push_back(num);
    }

    prefix.resize(arr.size());
    prefix[0] = 0;
    
    for(int idx=1; idx<arr.size() + 1; idx++) {
        prefix[idx] = prefix[idx - 1] + arr[idx - 1];
    }

    int l, r;
    for(int i=0; i<M; i++) {
        cin >> l >> r;
        cout << prefix[r] - prefix[l - 1] << "\n";
    }
}
