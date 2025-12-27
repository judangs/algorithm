#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

string S, copy_S = "";

int main() {

    cin >> S;
    for(auto c: S) copy_S += "@" + string(1, c);
    copy_S += '@';
    
    vector<int> P(2 * copy_S.size() + 2, 0);
    int center = -1, right = -1;
    for(int i = 0; i < copy_S.size(); i++) {
        if(i <= right) {
            P[i] = min(right - i, P[center - (i - center)]);
        }
        while(i + P[i] + 1 < copy_S.size() && 0 <= i - P[i] - 1 && copy_S[i + P[i] + 1] == copy_S[i - P[i] - 1])
            P[i]++;
        
        if(right < i + P[i]) {
            center = i;
            right = i + P[i];
        }
    }

    int answer = *max_element(P.begin(), P.end());
    cout << answer << endl;

}