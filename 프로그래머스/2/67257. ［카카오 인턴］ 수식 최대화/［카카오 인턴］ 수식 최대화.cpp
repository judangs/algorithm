#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <iostream>

using namespace std;

vector<string> ops = {"*", "+", "-"};

vector<long long> numbers;
vector<string> op;


long long calculate(long long a, long long b, string p) {
    if(p == "+")
        return a + b;
    else if(p == "-")
        return a - b;
    else
        return a * b;
}

long long solution(string expression) {

    string num = "";
    for(int i=0; i<expression.size(); i++) {
        if(isdigit(expression[i]) == false) {
            numbers.push_back(stoll(num));
            op.push_back(string(1, expression[i]));
            num = "";
        }
        else {
            num += expression[i];
        }
    }

    numbers.push_back(stoll(num));
    sort(ops.begin(), ops.end());


    long long answer = 0;
    do {
        vector<long long> number(numbers);
        vector<string> c_op(op);
        
        for(int i=0; i<ops.size(); i++) {
            vector<string>::iterator iter;
            while((iter = find(c_op.begin(), c_op.end(), ops[i])) != c_op.end()) {
                int idx = iter - c_op.begin();
                long long result = calculate(number[idx], number[idx + 1], *iter);
                
                number.erase(number.begin() + idx, number.begin() + idx + 2);
                number.insert(number.begin() + idx, result);
                c_op.erase(iter);
            }
        }

        answer = max(answer, abs(number.front()));
    } while(next_permutation(ops.begin(), ops.end()));

    return answer;
}