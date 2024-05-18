#include <iostream>
#include <string>
#include <stack>

using namespace std;

int T;

int main() {
    cin >> T;

    string land;
    for(int k=1; k<=T; k++) {

        stack<char> s;
        cin >> land;
        
        int answer = 0;
        for(int i=0; i<land.size()-1; i++) {
            if(land[i] == '(' && land[i + 1] == '|') {answer++; i++;}
            else if(land[i] == '|' && land[i + 1] == ')') {answer++; i++;}
            else if(land[i] == '(' && land[i + 1] == ')') {answer++; i++;}
        }

        cout << "#" << k << " ";
        cout << answer << endl;          
    }
}