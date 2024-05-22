#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

string to_binary(long long number) {
    string ret = "";
    while(number / 2 != 0) {
        ret += to_string(number % 2);
        number /= 2;
    }
    ret += "1";
    return ret;
}

long long check_diff(string bin, string plus_bin) {

    long long diff_count;
    if(bin.size() < plus_bin.size()) diff_count = 1;
    else diff_count = 0;

    for(int i=0; i<bin.size(); i++) {
        if(bin[i] != plus_bin[i]) diff_count++;
    }

    return diff_count;
}

long long to_decimal(string number) {
    long long ret = 0;
    for(int i=0; i<number.size(); i++) {
        ret += pow(2, i) * (number[i] - '0');
    }

    return ret;
}

long long change_value(string bin, string plus_bin, long long diff) {
    int ptr = 0;
    while(ptr < bin.size() &&  diff > 2) {
        if(bin[ptr] != plus_bin[ptr]) {
            if(plus_bin[ptr] == '0') {
                plus_bin[ptr] = '1';
            }
            else
                plus_bin[ptr] = '0';
            
            diff--;
        }

        ptr++;
    }

    return to_decimal(plus_bin);
}

vector<long long> solution(vector<long long> numbers) {
    vector<long long> answer;
    for(auto number: numbers) {
        string bin = to_binary(number);
        string plus_bin = to_binary(number + 1);

        long long diff = check_diff(bin, plus_bin);
        if(diff <= 2) {
            answer.push_back(to_decimal(plus_bin));
        }
        else {
            answer.push_back(change_value(bin, plus_bin, diff));  
        }
    }

    return answer;
}