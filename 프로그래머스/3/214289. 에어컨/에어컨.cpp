#include <string>
#include <vector>
#include <algorithm>
#include <memory.h>

using namespace std;

int cache[1001][51];
static int d[] = { -1, 0, 1 };

const int inf = 1e9;
int st, et, costa, costb;
int outdoor;

bool is_valid(int t) {
    return 0 <= t && t < 51;
}

int dfs(int depth, int now, int n, vector<int> & onboard) {
    
    if(depth == n) return 0;
    if(onboard[depth] == 1 && !(st <= now && now <= et)) return inf;
    
    int & ret = cache[depth][now];
    if(ret != -1) return ret;
    
    ret = inf;
    
    if(now == outdoor) ret = min(ret, dfs(depth + 1, now, n, onboard));
    else ret = min(ret, dfs(depth + 1, (now < outdoor ? now + 1 : now - 1), n, onboard));
    
    ret = min(ret, dfs(depth + 1, now, n, onboard) + costb);
    if(now + 1 < 51)
        ret = min(ret, dfs(depth + 1, now + 1, n, onboard) + costa);
    if(0 <= now - 1)
        ret = min(ret, dfs(depth + 1, now - 1, n, onboard) + costa);
    
    return ret;

}

int solution(int temperature, int t1, int t2, int a, int b, vector<int> onboard) {
    
    memset(cache, -1, sizeof(cache));
    
    int mt = min(temperature, t1);
    if(mt < 0) {
        temperature -= mt;
        t1 -= mt;
        t2 -= mt;
    }
    
    st = t1, et = t2;
    costa = a, costb = b;
    outdoor = temperature;    
    
    int ans = dfs(0, temperature, onboard.size(), onboard);
    return ans;
    
}