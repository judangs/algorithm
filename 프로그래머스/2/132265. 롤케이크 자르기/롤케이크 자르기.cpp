#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

map<int, int> user1, user2;


int solution(vector<int> topping) {
    
    queue<int> q;
    
    for(int topp: topping) {
        user1[topp]++;
        q.push(topp);
    }
    
    int answer = 0;
    while(!q.empty()) {
        int current = q.front();
    
        user1[current]--;
        if(user1[current] == 0) {
            user1.erase(current);
        }
        
        user2[current]++;
        
        if(user1.size() == user2.size()) {
            answer++;
        }
        
        q.pop();
    }
    
    return answer;
}