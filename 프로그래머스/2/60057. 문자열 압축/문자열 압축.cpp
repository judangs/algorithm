#include <string>
#include <iostream>

using namespace std;

int solution(string s) {

    if(s.size() == 1) return 1;

    string answer(1001, 'A');
    for(int i=1; i<=s.size()/2; i++) {
        string compress = "";
        for(int ptr=0; ptr<s.size();) {
            string pivot = s.substr(ptr, i);
            string next = pivot;
            
            int count = -1;
            while(pivot == next) {
                count++;
                ptr += i;
                if(ptr >= s.size()) break;
                next = s.substr(ptr, i);
            }
            
            if(count == 0) compress += pivot;
            else compress += (to_string(count + 1) + pivot);
        }

        if(compress.size() < answer.size())
            answer = compress;
    }

    return answer.size();
}