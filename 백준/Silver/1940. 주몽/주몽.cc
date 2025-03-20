#include <iostream>
#include <map>

using namespace std;

int N, M, A;
map<int, int> needs;

int main() {
    
    cin >> N >> M;

    int answer = 0;
    for(int i=0; i<N; i++) {
        cin >> A;
        if(needs[A] != 0) {
            answer++;
            needs[A]--;
        }
        else {
            needs[M - A]++;
        }
    }

    cout << answer;
}