#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N;
string pattern;

int main() {

    cin >> N;
    cin >> pattern;

    vector<string> file(N);
    for(int i=0; i<N; i++) {
        string name; cin >> name;
        file[i] = name;
    }

    for(auto name: file) {

        int n = pattern.size(), m = name.size();
        
        bool equal = true;
        int i, j, p;
        for(i = 0, p = 0; i<m && p < n && pattern[p] != '*'; i++, p++) {
            if(pattern[p] != name[i]) {
                equal = false; break;
            }
        }

        for(j=m - 1, p = n - 1; j >= 0 && p >= 0 && pattern[p] != '*'; j--, p--) {
            if(pattern[p] != name[j]) {
                equal = false; break;
            }
        }

        if(i > j + 1) equal = false;

        string answer = (equal ? "DA" : "NE");
        cout << answer << endl;
    }
}