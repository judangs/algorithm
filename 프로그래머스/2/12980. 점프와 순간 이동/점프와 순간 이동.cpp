#include <iostream>
using namespace std;

int solution(int n) {
    
    
    int answer;
    if(n % 2 != 0) answer = 1;
    else answer = 0;
    
    while(n != 0) {
        n /= 2;
        if(n % 2 != 0) {
            answer++;
            n--;
        }
    }
    
    return answer;
}
