#include <iostream>
#include <vector>
using namespace std;

int T;

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {

        vector<int> box(3);
        int value;
        for(int i=0; i<3; i++) {
            cin >> value;
            box[i] = value;
        }

        bool make = true;
        int count = 0;
        for(int i=2; i>0; i--) {
            if(box[i-1] == box[i]) {
                if(box[i-1] > 1) {
                    count++;
                    box[i-1]--;
                }
                else {
                    make = false;
                    break;
                }
            }
            else if(box[i-1] > box[i]) {
                int diff = box[i-1] - box[i] + 1;
                if(box[i-1] - diff > 0) {
                    count += diff;
                    box[i-1] -= diff;
                }
                else {
                    make = false;
                    break;
                }
            }
        }
        cout << "#" << k << " ";
        if(make)
            cout << count << endl;
        else
            cout << -1 << endl;
            
    }
}