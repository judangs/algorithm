#include <iostream>
#include <cstring>

using namespace std;

int T;

int main() {
    cin >> T;

    for(int k=1; k<=T; k++) {

        string cups;
        int count;
        cin >> cups >> count;
        int idx = cups.find("o");
        while(count > 0) {
            idx -= 1;
            if(idx == -1)
                idx = 1;
            count--;
        }

        cout << "#" << k << " " << idx << endl;
    }
}