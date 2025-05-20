#include <iostream>
#include <cstring>
#include <set>

using namespace std;

int C, N, Q;
string color, nickname, team;
set<string> person;

struct Trie {
    
    bool end;
    Trie * next[26];
    
    Trie() {
        end = false;
        for(int idx=0; idx<26; idx++) next[idx] = nullptr;
    }

    void insert(const char * w) {
        if(*w == '\0') {
            end = true;
            return;
        }
        
        int ch = *w - 'a';
        if(next[ch] == nullptr) 
            next[ch] = new Trie();
        
        next[ch]->insert(w + 1);
    }
    
    bool find(const char * w) {
        if(*w == '\0') return false;
        if(end) {
            if(person.find(w) != person.end())
                return true;
        }
        int ch = *w - 'a';
        if(next[ch] == nullptr) return false;
        return next[ch]->find(w + 1);
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    Trie * trie = new Trie();

    cin >> C >> N;
    for(int idx=0; idx<C; idx++) {
        cin >> color;
        trie->insert(color.c_str());
    }

    for(int idx=0; idx<N; idx++) {
        cin >> nickname;
        person.insert(nickname);
    }
    
    cin >> Q;
    for(int q=0; q<Q; q++) {
        cin >> team;
        bool result = trie->find(team.c_str());
        if(result) cout << "Yes\n";
        else cout << "No\n";
    }
    
}