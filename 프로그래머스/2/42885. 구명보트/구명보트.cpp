#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    int answer = 0;
    
    sort(people.begin(), people.end());
    int low_ptr=0, large_ptr = people.size()-1;
    
    int total;
    while(low_ptr < large_ptr) {
        total = people[large_ptr];
        
        int count = 0;
        if(total + people[low_ptr] <= limit)
            total += people[low_ptr++];
        
        /*
        while(total + people[low_ptr] <= limit) {
            total += people[low_ptr++];
        }
        */
        
        answer++;
        large_ptr--;
    }
    
    if(low_ptr == large_ptr) answer++;
    
    return answer;
}