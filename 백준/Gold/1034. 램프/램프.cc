#include <iostream>
#include <vector>
#include <map>

using namespace std;

int N, M, K;
map<string, int> pattern;

int main() {
    
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        string lamp; cin >> lamp;
        pattern[lamp]++;
    }

    cin >> K;

    int answer = 0;
    for(auto & [lamp, count]: pattern) {

        int zero = 0;
        for(auto & c: lamp)
            if(c == '0') zero++;

        if(zero <= K && zero % 2 == K % 2) {
            answer = max(answer, count);
        }
    }

    cout << answer << endl;
}

