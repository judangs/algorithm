#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long ll;

int T;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {

        int N; cin >> N;
        vector<pair<ll, ll>> person(N);
        for(auto & [score, meeting]: person) cin >> score >> meeting;

        sort(person.begin(), person.end());
        
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        
        int answer = 0;
        for(auto & [score, meeting]: person) {
            if(pq.empty()) {
                pq.push(meeting);
            }
            else {
                if(pq.top() >= meeting) 
                    pq.push(meeting);
            }

            answer = max(answer, (int) pq.size());
        }

        cout << answer << endl;

    }

}