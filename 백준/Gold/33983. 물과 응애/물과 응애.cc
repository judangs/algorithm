#include <iostream>
#include <cstring>

using namespace std;

int main() {

    int N;
    string S;
    cin >> N >> S;

    int H = 0, O = 0;

    int hp = 0, op = 0;
    for (char c : S) {
        if (c == 'H') hp++;
        else op++;
        if (hp < op) { cout << "mix\n"; return 0; }
    }

    int hs = 0, os = 0;
    for (int i = N - 1; i >= 0; --i) {
        if (S[i] == 'H') hs++;
        else os++;
        if (hs < os) { cout << "mix\n"; return 0; }
    }

    for (char c : S) (c == 'H' ? H : O)++;
    cout << ((H == 2 * O) ? "pure\n" : "mix\n");
}
