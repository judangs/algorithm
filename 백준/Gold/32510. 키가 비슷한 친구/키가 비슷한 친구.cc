#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <functional>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

using namespace std;
typedef long long ll;

int T, N, K;
struct Person {
    int idx;
    int A;

    bool operator>(const Person & o) const {
        return idx > o.idx;
    }
};

int main() {

    fastio;
    cin >> T;
    for(int t = 1; t <= T; t++) {
        
        cin >> N >> K;
        vector<Person> arr(N);
        for(int idx = 0; idx < N; idx++) {
            cin >> arr[idx].A;
            arr[idx].idx = idx;
        }

        sort(arr.begin(), arr.end(), [](const Person & l, const Person & r) {
            if(l.A == r.A)
                return l.idx < r.idx;
            return l.A < r.A;
        });

        priority_queue<Person, vector<Person>, greater<Person>> pq;

        ll answer = 0;
        for(int idx = 0; idx < N; idx++) {
            auto person = arr[idx];
            pq.push(person);
            
            while(!pq.empty() && pq.top().A < person.A - K)
                pq.pop();

            answer += abs(pq.top().idx - person.idx);
            
        }

        cout << "Case #" << t << endl;
        cout << answer << endl;

    }
}