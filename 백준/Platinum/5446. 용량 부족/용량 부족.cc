#include <iostream>
#include <map>

using namespace std;

int T, N;

struct Trie {
    
    int drop;
    int remain;
    bool end;
    map<char, Trie *> child;

    Trie() : drop(0), remain(0), end(false) {  }

    ~Trie() {
        for(auto iter = child.begin(); iter != child.end(); iter++)
            delete iter->second;
    }

    void insert(const char * w, bool flag) {
        
        if(flag) drop++;
        else remain++;

        if(*w == '\0') {
            if(flag) end = true;
            return;
        }

        if(child.find(*w) == child.end())
            child[*w] = new Trie();

        child[*w]->insert(w + 1, flag);
    }

};


int command(Trie * now) {

    if(0 < now->drop && now->remain == 0) 
        return 1;

    int ret = (now->end ? 1 : 0);
    for(auto iter=now->child.begin(); iter != now->child.end(); iter++)
        ret += command(iter->second);

    return ret;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {

        Trie * trie = new Trie();
        
        cin >> N;
        for(int i=0; i<N; i++) {
            string file; cin >> file;
            trie->insert(file.c_str(), true);
        }

        cin >> N;
        for(int i=0; i<N; i++) {
            string file; cin >> file;
            trie->insert(file.c_str(), false);
        }

        int answer = command(trie);
        cout << answer << endl;

        delete trie;

    }

}