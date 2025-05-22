#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int T, n, m;
string dna, marker;

struct Trie {

    bool end;
    Trie * fail;
    Trie * child[8];

    Trie() {
        end = false;
        for(int idx=0; idx<8; idx++)
            child[idx] = nullptr;
    }

    ~Trie() {
        for(int idx=0; idx<8; idx++)
            if(child[idx] != nullptr)
                delete child[idx];
    }

    void insert(const char * w) {
        if(*w == '\0') {
            end = true;
            return;
        }

        int ch = (*w - 'A') % 8;
        if(child[ch] == nullptr)
            child[ch] = new Trie();

        child[ch]->insert(w + 1);
    }

};

void build_failure_trie_path(Trie * root) {
    queue<Trie *> q;

    root-> fail = root;
    q.push(root);

    while(!q.empty()) {
        auto current = q.front();
        q.pop();
        
        for(int idx=0; idx<8; idx++) {
            auto next = current->child[idx];
            if(next != nullptr) {
                if(current == root) next->fail = root;
                else {
                    auto failure = current->fail;
                    while(failure != root && failure->child[idx] == nullptr)
                        failure = failure->fail;

                    if(failure->child[idx] != nullptr) failure = failure->child[idx];
                    
                    next->fail = failure;
                }

                if(next->fail->end)
                    next->end = true;
                q.push(next);
            }
        }
    }
}


int search_trie_kmp(const char * pattern, Trie * root) {
    
    auto current = root;

    int begin = 0, answer = 0;
    while(*pattern != '\0') {
        
        int ch = (*pattern - 'A') % 8;
        if(current->child[ch] != nullptr) {
            current = current->child[ch];
            pattern++;
            if(current->end) {
                answer++;
            }
        }
        else {
            if(current == root) pattern++;
            else {
                current = current->fail;    
            }
        }
    }

    return answer;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while(T--) {

        Trie * trie = new Trie();

        cin >> n >> m;
        cin >> dna >> marker;

        trie->insert(marker.c_str());
        for(int i=0; i<m; i++) {
            for(int j=i + 2; j<=m; j++) {
                reverse(marker.begin() + i, marker.begin() + j);
                trie->insert(marker.c_str());
                reverse(marker.begin() + i, marker.begin() + j);
            }
        }

        build_failure_trie_path(trie);
        cout << search_trie_kmp(dna.c_str(), trie) << "\n";

        delete trie;
    }
    
}