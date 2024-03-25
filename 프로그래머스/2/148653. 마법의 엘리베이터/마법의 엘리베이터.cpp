#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

int result = INT32_MAX;

void dfs(int depth, int offset, int storey, int length) {
    
    int pos = storey % (int) pow(10, depth + 1);
    int sub_pos = pos / (int) pow(10, depth);
    int add_pos = 10 - pos / (int) pow(10, depth);
    
    //cout << depth << " " << storey <<  " " << offset << endl;
    
    if(depth == length) {
        int top_pos = storey / (int) pow(10, depth);
        if(top_pos == 10) {
            result = min(result, offset + 1);
        }
        else {
            result = min(result, offset + min(sub_pos, add_pos + 1));
        }
        return;
    }
    
    if(add_pos == 10) add_pos = 0;
    
    dfs(depth + 1, offset + sub_pos, storey - sub_pos * pow(10, depth), length);
    dfs(depth + 1, offset + add_pos, storey + add_pos * pow(10, depth), length);
}

int solution(int storey) {
    int answer = 0;
    int length = to_string(storey).size();
    dfs(0, 0, storey, length);
    
    answer = result;
    return answer;
}