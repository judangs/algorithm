#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool compare(int a, int b) {
    string c_a = to_string(a);
    string c_b = to_string(b);
    
    return (c_a + c_b) > (c_b + c_a);
}

string solution(vector<int> numbers) {
    sort(numbers.begin(), numbers.end(), compare);
    if(*max_element(numbers.begin(), numbers.end()) == 0)
        return "0";

    string answer = "";
    for(int number: numbers) {
        answer += to_string(number);
    }

    return answer;
}