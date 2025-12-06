#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL);

using namespace std;
typedef pair<int, int> pii;

int main() {

    int n; cin >> n;
    vector<pair<int, int>> lecture(n);
    for(auto & [p, d]: lecture) cin >> p >> d;

    sort(lecture.begin(), lecture.end(), [](const pii & l, const pii & r) {
        if(l.first == r.first)
            return l.second < r.second;
        return l.first > r.first;
    });
    
    vector<bool> days(10001, false);

    int answer = 0;
    for(auto & [p, d]: lecture) {
        for(int last = d; 0 < last; last--) {
            if(!days[last]) {
                days[last] = true;
                answer += p;
                break;
            }
        }
    }

    cout << answer << endl;

}