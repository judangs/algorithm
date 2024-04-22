#include <string>
#include <iostream>

using namespace std;

string solution(int n) {
    string answer = "";
    
    while(n / 3 >= 1) {
        bool div_zero = false;
        if(n % 3 == 0) {
            answer = "4" + answer;
            div_zero = true;
        }
        else {
            answer = to_string(n % 3) + answer;
        }

        n /= 3;
        if(div_zero == true)
            n -= 1;
    }
    

    if(n != 0)    
        answer = to_string(n) + answer;

    return answer;
}