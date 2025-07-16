#include <iostream>
#include <stdlib.h>
#include <memory.h>

using namespace std;

int N;
int student[2][3];
int copys[2][3], pairs[3][3];

void pairing(int i, int j) {
    int count = min(copys[0][i], copys[1][j]);
    pairs[i][j] = count;
    copys[0][i] -= count, copys[1][j] -= count;
}

bool check(int i, int j, int k) {

    memset(pairs, 0, sizeof(pairs));
    memcpy(copys, student, sizeof(student));

    pairing(i, (i + 1) % 3), pairing(i, (i + 2) % 3);
    pairing(j, (j + 1) % 3), pairing(j, (j + 2) % 3);
    pairing(k, (k + 1) % 3), pairing(k, (k + 2) % 3);

    for(int i=0; i<2; i++)
        for(int j=0; j<3; j++) if(copys[i][j] != 0) return false;

    return true;
}

int main() {

    cin >> N;
    for(int i=0; i<3; i++) cin >> student[0][i] >> student[1][i];
    
    if(check(0, 1, 2) || check(1, 0, 2) || check(2, 0, 1)) {
        cout << "1" << endl;
        cout << pairs[0][1] << " " << pairs[0][2] << endl;
        cout << pairs[1][0] << " " << pairs[1][2] << endl;
        cout << pairs[2][0] << " " << pairs[2][1] << endl; 
    }
    else {
        cout << "0" << endl;
    }

}


