#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int result = INT32_MAX;

// 0: minus
// 1: plus
void dfs(int depth, vector<int> & parts, int length, int storey) {
    int count = 0;
    if(depth == length) {
        int div = 10;
        for(int i=parts.size()-1; i>=0; i--) {
            if(parts[i] == 0) {
                count += (storey % div);
                storey /= div;
            }
            else {
                if(storey % div != 0) {
                    count += (10 - storey % div);
                }
                storey /= div;
                storey += 1;
            }
            
            if(storey == 10 || storey == 1) {
                count++;
                break;
            }
        }
        
        if(count >= 0) result = min(result, count);
        return;
    }
    
    parts[depth] = 0;
    dfs(depth + 1, parts, length, storey);
    parts[depth] = 1;
    dfs(depth + 1, parts, length, storey);
    
}

int solution(int storey) {
    int answer = 0;
    int length = to_string(storey).size();
    vector<int> parts(length);
    dfs(0, parts, length, storey);
    
    answer = result;
    return answer;
}