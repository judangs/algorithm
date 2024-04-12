#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string convert_number(int n, int number) {
    string ret = "";
    while(number >= n) {
        int mod = number % n;
        if(mod >= 10)
            ret += (char)('A' + (mod % 10));
        else
            ret += to_string(number % n);            
        
        number /= n;
    }
    
    if(number >= 10) {
        ret += (char)('A' + (number % 10));
    }
    else
        ret += to_string(number);

    reverse(ret.begin(), ret.end());
    return ret;
}

string solution(int n, int t, int m, int p) {
    
    string number_array, answer = "";
    int turn = 0, current = p-1;
    for(int i=0; i<t*m; i++) {
        number_array = convert_number(n, i);
        for(int j=0; j<number_array.size(); j++) {
            if(turn == current) {
                answer += number_array[j];
                current += m;
                if(answer.size() == t)
                    return answer;
            }
            turn++;
        }
    }
}