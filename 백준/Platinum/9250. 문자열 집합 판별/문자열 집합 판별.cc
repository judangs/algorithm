#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N, Q;
string word;

struct Trie {
    bool end;
    Trie * fail;
    Trie * next[26];
    
    Trie() {
        end = false;
        fail = nullptr;
        for(int idx=0; idx<26; idx++) 
            next[idx] = nullptr;
    }

    void insert(const char * w) {
        if(*w == '\0') {
            end = true;
            return;
        }

        int ch = *w - 'a';
        if(next[ch] == nullptr)
            next[ch] = new Trie();
            
        next[ch]->insert(w +1);
    }
};


bool search(Trie * root, string pattern) {

    auto node = root;
    for(int idx=0; idx<pattern.size(); idx++) {
        int ch = pattern[idx] - 'a';
        while(node != root && node->next[ch] == nullptr) {
            node = node->fail;
        }

        if(node->next[ch] != nullptr)
            node = node->next[ch];

        if(node->end) return true;
    }

    return false;
}

void build_failure_path(Trie * root) {

    queue<Trie *> q;

    root->fail = root;
    q.push(root);

    while(!q.empty()) {
        auto node = q.front();
        q.pop();

        for(int ch=0; ch<26; ch++) {
            auto next = node->next[ch];
            if(next != nullptr) {
                if(node == root) next->fail = root;
                else {
                    auto fail = node->fail;
                    while(fail != root && fail->next[ch] == nullptr)
                        fail = fail->fail;

                    if(fail->next[ch] != nullptr) fail = fail->next[ch];
                    
                    next->fail = fail;
                    
                }

                if(next->fail->end) 
                    next->end = true;
                q.push(next);
            }        
        }
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    Trie * trie = new Trie();

    cin >> N;
    for(int idx=0; idx<N; idx++) {
        cin >> word;
        trie->insert(word.c_str());
    }

    build_failure_path(trie);

    cin >> Q;
    for(int q=0; q < Q; q++) {
        cin >> word;
        bool result = search(trie, word);
        if(result)  cout << "YES\n";
        else cout <<"NO\n";
    }

}