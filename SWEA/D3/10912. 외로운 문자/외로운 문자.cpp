#include <iostream>
#include <map>
#include <string>

using namespace std;

int T;

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        
        map<char, int> m;
        string array;
        cin >> array;

        for(int i=0; i<array.size(); i++) {
            m[array[i]]++;
        }

        string answer = "";
        for(auto iter=m.begin(); iter!=m.end(); iter++) {
            if(iter->second % 2 == 1) answer += iter->first;
        }

        cout << "#" << k << " ";
        if(answer.empty())  cout << "Good" << endl;
        else cout << answer << endl;
    }
}