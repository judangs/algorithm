#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, K, D;
struct Study {
    int level;
    vector<int> learn;

    bool operator<(const Study & o) const {
        return level < o.level;
    }
};

vector<Study> student;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K >> D;
    student.resize(N);
    for(int i=0; i<N; i++) {
        int m, d; cin >> m >> d;
        vector<int> l(m);
        for(auto & a: l) cin >> a;
        student[i] = {d, l};
    }

    sort(student.begin(), student.end());
    
    int left = 0, right = left + 1;
    vector<int> algorithms(K + 1, 0);
    for(auto & algo: student[left].learn) algorithms[algo]++;

    int answer = 0;
    while(right < N) {
        if(student[right].level - student[left].level <= D) {
            for(auto & algo: student[right].learn) algorithms[algo]++;
            
            int type = 0, wellkown = 0, member = (right - left + 1);
            for(int i=1; i<=K; i++) {
                if(algorithms[i]) type++;
                if(algorithms[i] == member) wellkown++;
            }

            answer = max(answer, (type - wellkown) * member);
            right++;
        }
        else {
            for(auto & algo: student[left].learn) algorithms[algo]--;
            left++;
        }
    }

    cout << answer << endl;

}