#include <iostream>
#include <cstring>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int, int> pii;

int N, M;
string emoticon, sentence;

struct Trie {
    
    bool end;
    Trie * fail;
    int size;
    unordered_map<char, Trie *> child;

    Trie() {
        end = false;
        size = 0;
        fail = nullptr;
    }

    ~Trie() {
        for(auto & entry: child)
            delete entry.second;
        child.clear();
    }

    void insert(const char * w, int p) {
        if(*w == '\0') {
            end = true;
            size = p;
            return;
        }

        if(child.find(*w) == child.end()) {
            child[*w] = new Trie();
        }
        
        child[*w]->insert(w + 1, p + 1);
    }
};


void build_failure_path(Trie * root) {
    queue<Trie *> q;
    
    root->fail = root;
    q.push(root);
    
    while(!q.empty()) {
        auto current = q.front();
        q.pop();
        
        for(auto iter = current->child.begin(); iter != current->child.end(); iter++) {
            
            char ch = iter->first;
            auto & next = iter->second;

            if(next != nullptr) {
                if(current == root) next->fail = root;
                else {
                    auto failure = current->fail;
                    while(failure != root && failure->child.find(ch) == failure->child.end()) {
                        failure = failure->fail;
                    }

                    if(failure->child.find(ch) != failure->child.end()) 
                        failure = failure->child[ch];

                    next->fail = failure;
                }

                if(next->fail->end)
                    next->end = true;

                q.push(next);
            }
        }
    }
}


int search(Trie * root, string s) {

    auto node = root;

    int count = 0;
    for(int idx=0; idx < s.size(); idx++) {

        char ch = s[idx];
        while(node != root && node->child.find(ch) == node->child.end()) {
            node = node->fail;
        }

        if(node->child.find(ch) != node->child.end())
            node = node->child[ch];
        
        if(node->end) {
            count++;
            node = root;
        }
    }

    return count;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    while(cin >> N >> M) {

        if(N == 0 && M == 0) break;

        Trie * trie = new Trie();

        for(int idx=0 ;idx<N; idx++) {
            cin >> emoticon;
            trie->insert(emoticon.c_str(), 0);
        }

        build_failure_path(trie);

        cin.ignore();

        int answer = 0;
        for(int idx=0; idx<M; idx++) {
            getline(cin, sentence);
            answer += search(trie, sentence);
        }

        cout << answer << "\n";
        
        delete trie;
    }

}