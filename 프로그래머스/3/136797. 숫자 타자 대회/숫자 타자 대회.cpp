#include <string>
#include <vector>
#include <memory.h>

using namespace std;


const int inf = 1e9;
int mdistance = inf;
vector<vector<int>> cost = {
    //  0 1 2 3 4 5 6 7 8 9 * #
    { 1,7,6,7,5,4,5,3,2,3,2,2}, // 0
    { 7,1,2,4,2,3,5,4,5,6,6,8}, // 1
    { 6,2,1,2,3,2,3,5,4,5,7,7}, // 2
    { 7,4,2,1,5,3,2,6,5,4,8,6}, // 3
    { 5,2,3,5,1,2,4,2,3,5,4,6}, // 4
    { 4,3,2,3,2,1,2,3,2,3,5,5}, // 5
    { 5,5,3,2,4,2,1,5,3,2,6,4}, // 6
    { 3,4,5,6,2,3,5,1,2,4,2,5}, // 7
    { 2,5,4,5,3,2,3,2,1,2,3,3}, // 8
    { 3,6,5,4,5,3,2,4,2,1,5,2}, // 9
    { 2,6,7,8,4,5,6,2,3,5,1,4}, // *
    { 2,8,7,6,6,5,4,5,3,2,4,1}  // #
};

int cache[100000][12][12];

int convert(char ch) {
    if(ch == '*') return 10;
    if(ch == '#') return 11;
    return (ch - '0');
}

int dfs(int depth, char left, char right, const string & numbers) {
    
    if(depth == numbers.size()) return 0;
    if(left == right) return inf;
    
    int l = convert(left), r = convert(right), next = convert(numbers[depth]);
    int & ret = cache[depth][l][r];
    if(ret != -1) return ret;
    
    ret = inf;
    
    ret = min(ret, dfs(depth + 1, numbers[depth], right, numbers) 
              + cost[l][next]);
    ret = min(ret, dfs(depth + 1, left, numbers[depth], numbers) 
              + cost[r][next]);
    
    
    return ret;
}

int solution(string numbers) {
    
    memset(cache, -1, sizeof(cache));
    return dfs(0, '4', '6', numbers);
}