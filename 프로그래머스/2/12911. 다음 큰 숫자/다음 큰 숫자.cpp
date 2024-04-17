#include <string>
#include <vector>
#include <iostream>

using namespace std;

int translation(int n) {
    int ret = 0;
    while(n != 1) {
        if(n % 2 == 1)
            ret++;
        n /= 2;
    }

    return ret;
}

bool check_condition(int n, int number) {
    return translation(n) == translation(number);
}

int solution(int n) {

    int current = n + 1;
    while(check_condition(n, current) == false) {
        current++;
    }
    
    return current;
}