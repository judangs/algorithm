#include <iostream>
#include <deque>

using namespace std;

int N, L, A;

struct Node {
    int idx;
    int num;
};

deque<Node> dq;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> L;
    for(int idx=0; idx<N; idx++) {
        cin >> A;

        while(!dq.empty() && dq.back().num >= A) {
            dq.pop_back();
        }

        while(!dq.empty() && dq.front().idx < idx - L + 1) {
            dq.pop_front();
        }

        dq.push_back({idx, A});
        cout << dq.front().num << " ";
    }
}