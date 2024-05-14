#include <iostream>

using namespace std;

int T;

bool solve(string message) {

    int n = message.size();
    int start, end;
    if(n % 2 == 0) {
        start = n / 2 -1;
        end = n / 2;
    }
    else {
        start = n / 2 - 1;
        end = n / 2 + 1;
    }

    while(start != -1 && end != n) {
        if(message[start] != message[end])
            break;
        start--;
        end++;
    }

    return (start == -1 ? true : false);
}

int main() {
    cin >> T;
    
    string message;
    for(int k=1; k<=T; k++) {
        cin >> message;

        
        cout << "#" << k << " ";
        int n = message.size();
        if(solve(message)) {
            if(n % 2 == 0) {
                if(solve(message.substr(0, n/2)) && solve(message.substr(n/2))) {
                    cout << "YES" << endl;
                }
                else
                    cout << "NO" << endl;
            }
            else {
                if(solve(message.substr(0, n/2)) && solve(message.substr(n/2+1))) {
                    cout << "YES" << endl;
                }
                else
                    cout << "NO" << endl;
            }
        }
        else {
            cout << "NO" << endl;
        }
    }
}