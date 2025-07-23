#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

string event;

int main() {

    cin >> event;
    int n = event.size();
    
    int answer = 0;
    for(int l=0; l<n; l++) {
        vector<bool> visit(27, false);
        visit[event[l] - 'a'] = true;

        int r = l + 1;
        while(r < n && event[l] != event[r]) {
            if(!visit[event[r] - 'a']) {
                visit[event[r] - 'a'] = true;
                answer++;
            }
            r++;
        }
    }

    cout << answer << endl;
}