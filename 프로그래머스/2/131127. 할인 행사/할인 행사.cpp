#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

map<string, int> buy_list;
map<string, int> sale;

bool check_want_list() {
    for(auto iter=buy_list.begin(); iter!=buy_list.end(); iter++) {
        string want_item = iter->first;
        if(iter->second > sale[want_item])
            return false;
    }
    
    return true;
}

int solution(vector<string> want, vector<int> number, vector<string> discount) {
    for(int i=0; i<want.size(); i++) {
        buy_list[want[i]] = number[i];
    }

    for(int i=0; i<10; i++) {
        sale[discount[i]]++;
    }

    int answer = 0;
    if(check_want_list())
        answer++;

    int start = 0, end = 10;
    while(end < discount.size()) {
        sale[discount[start++]]--;
        sale[discount[end++]]++;

        if(check_want_list()) {
            answer++;
        }  
    }

    return answer;
}