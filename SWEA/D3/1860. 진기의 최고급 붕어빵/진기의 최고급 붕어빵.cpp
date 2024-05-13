#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N, M, K;

string solve(vector<int> & timetable) {
    if(timetable.front() == 0)
        return "Impossible";
    int n = timetable.back();
    int bbang = 0;
    int ptr = 0;
    for(int current=1; current<=n; current++) {
        if(current % M == 0) bbang += K;
        if(current == timetable[ptr]) {
            if(bbang == 0)
                return "Impossible";
            else {
                bbang--;
                ptr++;
            }
        }
    }
    return "Possible";
}

int main() {
    cin >> T;
    for(int i=1; i<=T; i++) {
        cin >> N >> M >> K;

        vector<int> timetable;
        int t;
        for(int i=0; i<N; i++) {
            cin >> t;
            timetable.push_back(t);
        }
        sort(timetable.begin(), timetable.end());
        cout << "#" << i << " " << solve(timetable) << endl;
        timetable.clear();
    }
}