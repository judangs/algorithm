#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string solution(string number, int k) {

    int n = number.size() - k;
    int pick = -1;

    string answer = "";
    for(int  i=n; i>0; i--) {
        int max_value = -1;
        for(int j=pick + 1; j<=number.size()-i; j++) {
            int compare = number[j] - '0';
            if(max_value < compare) {
                max_value = compare;
                pick = j;
            }
        }

        answer += number[pick];
    }

    return answer;   
}