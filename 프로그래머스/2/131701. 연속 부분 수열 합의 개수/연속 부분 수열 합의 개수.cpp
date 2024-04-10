#include <string>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

int solution(vector<int> elements) {
    
    set<int> answer;
    for(int i=0; i<elements.size(); i++) {
        int start = 0;
        int end = start + i;
        int total = 0;
        for(int j=start; j<=end; j++) {
            total += elements[j % elements.size()];
        }

        answer.insert(total);
    
        while(start < elements.size()) {
            total -= elements[start++ % elements.size()];
            total += elements[++end % elements.size()];

            answer.insert(total);
        

            if(end >= elements.size()) {
                end %= elements.size();
            }
        }
    }

    return answer.size();
}