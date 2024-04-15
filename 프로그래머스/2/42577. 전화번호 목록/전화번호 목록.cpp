#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

map<string, int> m;

bool solution(vector<string> phone_book) {

    for(string phone: phone_book) {
        m[phone]++;
    }

    for(string phone: phone_book) {
        for(int i=0; i<phone.size()-1; i++) {
            if(m[phone.substr(0, i + 1)])
                return false;
        }
    }

    return true;
}