#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
string origin, target;

void on_click(string & bulbs, int idx) {
    bulbs[idx] = (bulbs[idx] == '0' ? '1' : '0');
    if(0 <= idx - 1) bulbs[idx -1] = (bulbs[idx - 1] == '0' ? '1' : '0');
    if(idx + 1 < bulbs.size()) bulbs[idx + 1] = (bulbs[idx + 1] == '0' ? '1' : '0');
    
}

int solve(bool click) {

    string current = origin;
    int count = 0;
    if(click) {
        on_click(current, 0);
        count++;
    }

    for(int idx=1; idx<current.size(); idx++) {
        if(current[idx - 1] != target[idx - 1]) {
            on_click(current, idx);
            count++;
        }
    }

    return (current == target ? count : -1);
}

int main() {
    
    cin >> N;
    cin >> origin >> target;

    int first = solve(true);
    int second = solve(false);

    if(first == -1) cout << second;
    else if(second == -1) cout << first;
    else {
        cout << min(first, second);
    }

    
}