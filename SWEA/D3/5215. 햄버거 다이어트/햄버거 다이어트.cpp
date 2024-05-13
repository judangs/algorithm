#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int T, N, L;
vector<pair<int, int>> dishes;
vector<bool> visit;
int result = 0;


void dfs(int current, int kal, int ptr) {
    if(kal > L) {
        return;
    }

    if(result < current)
        result = current;
    
    for(int i=ptr; i<dishes.size(); i++) {
        if(visit[i] == false && kal + dishes[i].second <= L) {
            visit[i] = true;
            dfs(current + dishes[i].first, kal + dishes[i].second, i + 1);
            visit[i] = false;
        }
    }
}

int main() {

    //freopen("input.txt", "r", stdin);
    cin >> T;
    int t, kal;
    for(int k=1; k<=T; k++) {
        cin >> N >> L;
        dishes.resize(N);
        for(int i=0; i<N; i++) {
            cin >> t >> kal;
            dishes[i] = {t, kal};
        }

        visit.resize(dishes.size(), false);

        dfs(0, 0, 0);
        dishes.clear();
        cout << "#" << k << " " << result << endl;
        result = 0;
    }

}