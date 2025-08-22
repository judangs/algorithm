#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>

using namespace std;

int n;
struct Work {
    int start, end;
};
stack<Work> st;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> n;
    vector<Work> works(n);
    for(int i=0; i<n; i++) {
        int d, t; cin >> d >> t;
        works[i] = {t - d + 1, t};
    }

    sort(works.begin(), works.end(), [](const Work & l, const Work & r) {
        if(l.end == r.end) {
            return l.start > r.start;
        }
        return l.end > r.end;
    });

    Work before = works.front();
    for(int i=1; i<n; i++) {
        if(before.start <= works[i].end) {
            int diff = works[i].end - (before.start - 1);
            before = {works[i].start - diff, works[i].end - diff};
        }
        else {
            before = works[i];
        }
    }

    int answer = before.start - 1;
    cout << answer << endl;
    

}