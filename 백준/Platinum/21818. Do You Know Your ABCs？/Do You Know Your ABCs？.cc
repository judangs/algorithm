#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

int T, N;
map<vector<int>, bool> visited;
int answer = 0;

void dfs(int depth, int edepth, int sum, vector<int> & now, vector<int> & num, set<int> & made, vector<bool> & visit) {
    
    if(sum != 0 && find(num.begin(), num.end(), sum) != num.end())
        made.insert(sum);

    if(depth == edepth) return;

    for(int i=0; i < now.size(); i++) {
        if(!visit[i]) {
            visit[i] = true;
            dfs(depth + 1, edepth, sum + now[i], now, num, made, visit);
            visit[i] = false;
        }
    }
    
}

bool valid(vector<int> & now, vector<int> & num) {

    set<int> made;

    vector<bool> visit(now.size(), false);
    dfs(0, 3, 0, now, num, made, visit);

    return ((int) made.size() == N);
}

void pick(int d, int ptr, vector<int> & now, vector<int> & pool, vector<int> & num) {
    if(d == 3) {
        
        auto temp = now;
        sort(temp.begin(), temp.end());

        if(!visited[temp] && valid(temp, num)) {
            visited[temp] = true;
            answer++;
        }

        return;
    }

    for(int idx=ptr; idx<pool.size(); idx++) {
        now.push_back(pool[idx]);
        pick(d + 1, idx + 1, now, pool, num);
        now.pop_back();
    }
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {
        
        cin >> N;
        vector<int> num(N + 1); num[0] = 0;
        for(int i=1; i<=N; i++) cin >> num[i];

        sort(num.begin(), num.end());

        vector<int> pool;
        for(int i=1; i<=N; i++)
            for(int j=0; j<i; j++)
                pool.push_back(num[i] - num[j]);


        vector<int> now;
        pick(0, 0, now, pool, num);

        cout << answer << endl;

        answer = 0;
        visited.clear();
        
    }


}