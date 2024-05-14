#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

int T;

int main() {
    cin >> T;
    
    string cards;
    for(int k=1; k<=T; k++) {
        cin >> cards;

        int count = 0;
        for(auto & card: cards) {
            if(card == '1') count++;
        }

        cout << "#" << k << " ";
        cout << (count % 2 == 1 ? "yes" : "no") << endl;
    }
}