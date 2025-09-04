#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;

int N;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<int> arr(N);
    for(auto & num: arr) cin >> num;

    vector<pair<int, int>> order(N);
    for(int i=0; i<N; i++)
        order[i] = {i, arr[i]};

    sort(order.begin(), order.end(), [](const pii & l, const pii & r) {
        return l.second < r.second;
    });

    vector<pair<int, int>> order2idx(N);
    order2idx[0] = {0, order[0].first};
    for(int rank=0, ptr = 1; ptr < N; ptr++) {
        if(order[ptr - 1].second == order[ptr].second)
            order2idx[ptr] = { rank, order[ptr].first };
        else
            order2idx[ptr] = { ++rank, order[ptr].first };
    }

    sort(order2idx.begin(), order2idx.end(), [](const pii & l, const pii & r) {
        return l.second < r.second;
    });

    for(auto & [rank, index]: order2idx) {
        cout << rank << " ";
    }
    

}