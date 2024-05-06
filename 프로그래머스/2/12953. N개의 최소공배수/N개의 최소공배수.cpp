#include <string>
#include <vector>
#include <iostream>

using namespace std;

int gcd(int a, int b) {
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

int solution(vector<int> arr) {
    int answer = 1;
    for(int number: arr) {
        answer = (answer * number) / gcd(answer, number);
    }

    return answer;
}