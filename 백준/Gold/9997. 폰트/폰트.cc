#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int answer = 0;
vector<int> words(26);

void make(int d, int pick, int ptr, int state) {
    
    if(state == (1 << 26) - 1) 
        answer++;

    if(d == pick) return;

    for(int idx=ptr; idx<N; idx++)
        make(d + 1, pick, idx + 1, state | words[idx]);

}

int main() {

    cin >> N;
    for(int i=0; i<N; i++) {
        string word; cin >> word;
        
        int state = 0;
        for(auto & ch: word) state |= (1 << (ch - 'a'));
        words[i] = state;

    }

    make(0, N, 0, 0);
    cout << answer << endl;
    
}