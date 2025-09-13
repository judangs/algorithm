#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, L, K;
struct Problem {
    int easy, hard;
    
    bool operator<(const Problem & o) const {
        if(hard == o.hard) return easy < o.easy;
        return hard < o.hard;
    }
};
vector<Problem> test;

int main() {

    cin >> N >> L >> K;
    test = vector<Problem> (N);
    for(int i = 0; i < N; i++) {
        int sub1, sub2; cin >> sub1 >> sub2;
        test[i] = { sub1, sub2 };
    }

    sort(test.begin(), test.end());

    int answer = 0;
    for(int i = 0, solved = 0; i< N && solved < K; i++) {
        if(test[i].hard <= L) {
            answer += 140, solved++;
        }
        else if(test[i].easy <= L) {
            answer += 100, solved++;
        }
    }
    
    cout << answer << endl;

}