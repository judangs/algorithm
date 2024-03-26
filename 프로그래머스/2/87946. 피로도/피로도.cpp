#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> array_dun;
vector<bool> visit;

int result = 0;

void dfs(int depth, int k, int count) {
    
    result = max(result, count);
    
    for(int i=0; i<array_dun.size(); i++) {
        if(visit[i] == false && array_dun[i].first <= k) {
            visit[i] = true;
            dfs(depth + 1, k - array_dun[i].second, count + 1);
            visit[i] = false;
        }
    }
} 

int solution(int k, vector<vector<int>> dungeons) {
    for(auto dungeon: dungeons) {
        array_dun.push_back(make_pair(dungeon[0], dungeon[1]));
    }
    
    visit.resize(array_dun.size(), false);
    
    dfs(0, k, 0);
    return result;
    
}