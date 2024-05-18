#include <iostream>
#include <string>

using namespace std;

int T;
string result = "NO";

void dfs(int depth, int count) {
    if(depth == 15) {
        if(count >= 8) result = "YES";
        return;
    }

    dfs(depth + 1, count + 1);
    dfs(depth + 1, count);
}

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        string win;
        cin >> win;
        
        int count = 0;
        for(auto & c: win) {
            if(c =='o') count++;
        }

        dfs(win.size(), count);
        cout << "#" << k << " ";
        cout << result << endl;
        result = "NO";
    }
}