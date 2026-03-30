#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int permutation(int depth, int n, vector<int> & now, vector<vector<int>> & q, vector<int> & ans) {
    
    if(depth == 5) {
        int idx = 0;
        for(auto & qi: q) {
            int count = 0;
            for(auto & qii: qi) {
                if(find(now.begin(), now.end(), qii) != now.end())
                    count++;
            }
            
            if(ans[idx] != count) {
                return 0;
            }
            
            idx++;
        }
        
        return 1;
    }
    
    int ret = 0;
    
    int init = (now.empty() ? 1 : now.back() + 1);
    for(int i = init; i <= n; i++) {
        now.push_back(i);
        ret += permutation(depth + 1, n, now, q, ans);
        now.pop_back();
    }
    
    return ret;
    
}

int solution(int n, vector<vector<int>> q, vector<int> ans) {
    
    vector<int> now;
    int answer = permutation(0, n, now, q, ans);
    return answer;
    
}