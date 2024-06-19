#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int compare_char(string s, int left, int right) {

    int count = 0;
    while(0 <= left && right < s.size()) {
        if(s[left] != s[right]) break;
        
        count += 2;
        left--;
        right++;
    }

    return count;
}

int get_palindrome(string s, int pivot) {

    int size;
    if(pivot + 1 < s.size() && s[pivot] == s[pivot + 1]) {
        size = max(compare_char(s, pivot, pivot + 1), 1 + compare_char(s, pivot - 1, pivot + 1));
    }
    else {
        size = 1 + compare_char(s, pivot - 1, pivot + 1);
    }

    return size;
}

int solution(string s) {
    
    int answer = 0;
    for(int current=0; current<s.size(); current++) {
        answer = max(answer, get_palindrome(s, current));
    }

    return answer;
}