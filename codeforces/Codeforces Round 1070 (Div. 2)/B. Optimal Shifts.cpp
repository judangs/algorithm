#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int t;
 
int main() {
 
    cin >> t;
    while(t--) {
        int n; cin >> n;
        string s; cin >> s;
        s = s + s;
 
        vector<int> zindex;
        int answer = 0;
        for(int i = 0; i < 2 * n; i++) {
            if(s[i] == '0')
                zindex.push_back(i);
            else
                zindex.clear();
 
            answer = max(answer, (int) zindex.size());
        }
 
        cout << answer << "\n";
 
    }
 
}
