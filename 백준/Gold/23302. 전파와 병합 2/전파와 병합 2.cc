#include <iostream>
#include <vector>
#include <cstring>
#include <vector>
#include <cctype>

#define MAXVERTEX 1000 * 702

using namespace std;

int R, C;
struct Edge {
    int start, end;
};
vector<vector<int>> adj(MAXVERTEX);

void build(int now, pair<int, int> matrix) {
    int ref = matrix.first * C + matrix.second;
    adj[ref].push_back(now);
}

pair<int, int> parse(string node) {
    string row = "", col = "";
    for(auto & ch: node) {
        if(isdigit(ch)) row += ch;
        else col += ch;
    }

    int column;
    if(col.size() == 1) column = col.front() - 'A';
    else {
        column = (col.front() - 'A' + 1) * 26 + (col.back() - 'A');
    }

    return { stoi(row) - 1, column };
}

bool dfs(int now, vector<int> & visit) {

    if(visit[now]) {
        if(visit[now] == -1) return true;
        return false;
    }
    
    visit[now] = -1;
    for(auto next: adj[now]) {
        if(dfs(next, visit)) return true;
    }

    visit[now] = 1;
    return false;
}

int main() {
    
    cin >> R >> C;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            string node; cin >> node;

            if(node == ".") continue;
            int now = i * C + j;
            if(node.find('+') == string::npos) {
                build(now, parse(node));
            }
            else {
                string first = node.substr(0, node.find('+'));
                string second = node.substr(node.find('+') + 1);

                build(now, parse(first));
                build(now, parse(second));
                
            }
        }
    }

    vector<int> visit(MAXVERTEX, 0);
    bool find = false;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            int cell = i * C + j;
            if(dfs(cell, visit))
                find = true;
        }
    }

    cout << (find ? "yes" : "no") << endl;
    

}