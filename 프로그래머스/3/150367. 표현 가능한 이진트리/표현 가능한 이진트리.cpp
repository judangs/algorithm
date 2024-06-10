#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

string to_bin(long long number) {
    string ret = "";
    while(number / 2 != 0) {
        ret += to_string(number % 2);
        number /= 2;
    }
    ret += string(1, '1');

    int k = 0;
    while(pow(2, k) - 1 < ret.size()) {
        k++;
    }
    reverse(ret.begin(), ret.end());
    ret = string(((pow(2, k) - 1) - ret.size()), '0') + ret;
    return ret;
}

bool check_tree(long long start, long long end, string bin) {

    if(start + 1 == end)
        return true;

    long long middle = (start + end) / 2;
    long long left = (start + middle) / 2;
    long long right = (middle + 1 + end) / 2;

    if(bin[middle] == '0') {
        if(bin[left] == '1' || bin[right] == '1') {
            return false;
        }
    }

    return check_tree(start, middle, bin) && check_tree(middle + 1, end, bin);
}

vector<int> solution(vector<long long> numbers) {

    vector<int> answer;
    for(long long number: numbers) {
        string num_to_bin = to_bin(number);
        
        bool result = check_tree(0, num_to_bin.size(), num_to_bin);
        
        if(result == true) answer.push_back(1);
        else answer.push_back(0);
    }

    return answer;
}