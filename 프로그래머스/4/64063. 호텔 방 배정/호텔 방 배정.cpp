#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;


unordered_map<long long, long long> parent;

long long find(long long start) {
    if(parent[start] == 0) {
        return start;
    }
    
    return parent[start] = find(parent[start]);
}

vector<long long> solution(long long k, vector<long long> room_number) {
    
    vector<long long> answer;
    for(long long room: room_number) {
        answer.push_back(find(room));
        parent[answer.back()] = answer.back() + 1;
    }
    
    return answer;
}