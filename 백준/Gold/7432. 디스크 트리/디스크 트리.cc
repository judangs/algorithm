#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

int N;

struct Trie {

    map<string, Trie *> child;

    void insert(int d, vector<string> & path) {
        if(d == path.size()) return;
        
        if(child.find(path[d]) == child.end())
            child[path[d]] = new Trie();

        child[path[d]]->insert(d + 1, path);
    }
}trie;

vector<string> parser(string dir) {
    stringstream iss(dir);
    string buffer;
    vector<string> ret;

    while(getline(iss, buffer, '\\')) {
        ret.push_back(buffer);
    }

    return ret;
}

void dfs(int depth, Trie * trie) {

    string blank(depth, ' ');
    for(auto iter=trie->child.begin(); iter != trie->child.end(); iter++) {
        cout << (blank + iter->first) << "\n";
        dfs(depth + 1, iter->second);
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int i=0; i<N; i++) {
        string dir; cin >> dir;
        vector<string> path = parser(dir);
        trie.insert(0, path);
    }

    dfs(0, &trie);


}