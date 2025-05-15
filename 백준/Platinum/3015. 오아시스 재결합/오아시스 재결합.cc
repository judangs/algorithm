#include <iostream>
#include <stack>

#define INF 1e18

using namespace std;

typedef long long ll;

int N, A;
stack<pair<ll, int>> st;

int main() {

    cin >> N;

    ll answer = 0;
    for(int idx=0; idx<N; idx++) {
        cin >> A;

        if(st.empty()) {
            st.push({A, 1});
            continue;
        }

        pair<ll, int> next = {A, 1};
        while(!st.empty() && st.top().first <= A) {
            if(st.top().first == next.first)
                next.second += st.top().second;
            answer += st.top().second;
            st.pop();
        }

        if(!st.empty()) {
            answer++;
        }

        st.push(next);
    }

    cout << answer << "\n";
}