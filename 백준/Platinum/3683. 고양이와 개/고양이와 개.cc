#include <iostream>
#include <vector>
#include <algorithm>

#define MAXVOTER 501

using namespace std;

int T, c, d, v;
string pass, fail;

struct Choice {
    char ptype;
    int pass;
    char ftype;
    int fail;
};

vector<Choice> vote;
vector<vector<int>> adj;
vector<int> matched;


bool matching(int current, vector<bool> & visit) {
    for(auto next: adj[current]) {
        if(!visit[next]) {
            visit[next] = true;

            if(matched[next] == -1 || matching(matched[next], visit)) {
                matched[next] = current;
                return true;
            }
        }
    }

    return false;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {
        cin >> c >> d >> v;
        
        for(int i=0; i<v; i++) {
            cin >> pass >> fail;
            vote.push_back({ pass.front(), stoi(pass.substr(1)), fail.front(), stoi(fail.substr(1))});
        }

        adj.resize(MAXVOTER);
        for(int i=0; i<v; i++) {
            for(int j=0; j<v; j++) {
                if(i == j) continue;
                auto v1 = vote[i], v2 = vote[j];
                if(v1.ptype == v2.ftype && v1.pass == v2.fail) adj[i].push_back(j);
                if(v1.ftype == v2.ptype && v1.fail == v2.pass) adj[i].push_back(j);
            }
        }

        vector<bool> visit(v, false);
        matched.resize(v, -1);

        int cond = 0;
        for(int i=0; i<v; i++) {
            fill(visit.begin(), visit.end(), false);
            if(matching(i, visit))
                cond++;
        }

        cout << (v - cond / 2) << "\n";

        vote.clear();
        adj.clear();
        matched.clear();

    }
}