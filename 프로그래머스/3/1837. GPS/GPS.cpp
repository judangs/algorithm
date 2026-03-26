#include <vector>
#include <algorithm>

#define INF 1e9

using namespace std;

vector<vector<int>> dist;
vector<vector<int>> cache;

int trace(int depth, int node, int n, vector<int> & log) {
    
    if(depth == log.size() - 2) {
        if(dist[node][log.back()] <= 1) return 0;
        return INF;
    }
    
    int & ret = cache[depth][node];
    if(ret != -1) return ret;
    
    ret = INF;
    for(int next = 1; next <= n; next++) {
        if(dist[node][next] <= 1) {
            if(log[depth + 1] != next)
                ret = min(ret, trace(depth + 1, next, n, log) + 1);
            if(log[depth + 1] == next)
                ret = min(ret, trace(depth + 1, next, n, log));
        }
    }
    
    return ret;
    
}

int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    
    dist = vector<vector<int>> (n + 1, vector<int>(n + 1, INF));
    cache = vector<vector<int>> (k, vector<int>(n + 1, -1));
    
    for(auto & edge: edge_list) {
        int s = edge.front(), e = edge.back();
        dist[s][e] = 1, dist[e][s] = 1;
    }
    
    for(int node = 1; node <= n; node++)
        dist[node][node] = 0;
    
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(k == i || k == j) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    int ans = trace(0, gps_log.front(), n, gps_log);
    ans = (ans == INF ? -1 : ans);
    return ans;
    
}