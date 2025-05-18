#include <iostream>
#include <cstring>

#define MAXWORD 100001

using namespace std;

int N;
string words[MAXWORD];

struct Trie {
    int visit;
    bool end;
    int create;
    Trie * next[26];

    ~Trie() {
        for(int idx=0; idx<26; idx++)
            if(next[idx] != nullptr) delete next[idx];
    }

    void init() {
        visit = 0;
        create = 0;
        end = false;
        for(int idx=0; idx<26; idx++) next[idx] = nullptr;
    }

    void insert(int d, string str) {

        visit++;

        if(d == str.size()) {
            end = true;
            return;
        }

        int ch = str[d] - 'a';
        if(next[ch] == nullptr) {
            create++;
            next[ch] = new Trie();
            next[ch]->init();
        }

        next[ch]->insert(d + 1, str);
    }

    double query(int d, string str, double count) {
        if(d == str.size()) return count;

        int ch = str[d] - 'a';

        if(d == 0) return next[ch]->query(d + 1, str, count + 1);
        if(end) return next[ch]->query(d + 1, str, count + 1);
        if(create > 1) return next[ch]->query(d + 1, str, count + 1);
        return next[ch]->query(d + 1, str, count);
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    while(cin >> N) {

        Trie * root = new Trie();
        for(int idx=0; idx<N; idx++) {
            cin >> words[idx];
            root->insert(0, words[idx]);
        }

        double answer = 0.0;
        for(int idx=0; idx<N; idx++) {
            answer += root->query(0, words[idx], 0.0);
        }

        cout.precision(2);
        cout << fixed << (answer / (double) N) << "\n";

        delete root;
        
    }

}