#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

queue<string> group1;
queue<string> group2;

int T, N;

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        cin >> N;
        
        string value;
        for(int i=0; i<N; i++) {
            cin >> value;
            if(N % 2 == 0) {
                if(i < N/2) {
                    group1.push(value);
                }
                else {
                    group2.push(value);
                }
            }
            else {
                if(i < (N/2) + 1) {
                    group1.push(value);
                }
                else {
                    group2.push(value);
                }   
            }
        }

        int current = 0;
        cout << "#" << k << " ";
        while(current < N) {
            if(current % 2 == 0) {
                cout << group1.front() << " ";
                group1.pop();
            }
            else {
                cout << group2.front() << " ";
                group2.pop();
            }

            current++;
        }
        cout << endl;
    }
}
