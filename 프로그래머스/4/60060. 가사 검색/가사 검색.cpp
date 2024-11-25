#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Trie {
    
    Trie * next[27];
    int count;
    
    Trie() {
        for(int idx=0; idx<27; idx++) {
            next[idx] = nullptr;
        }
        
        count = 0;
    }
    
    void insert(const char * word) {
        
        if(*word == '\0')
            return;
            
        int w = *word - 'a';
        if(next[w] == nullptr)
            next[w] = new Trie();
        
        count++;
        next[w]->insert(++word);
    }
    
    void revinsert(const char * word, int ptr) {
        
        if(ptr < 0)
            return;

        int w = *word - 'a';
        if(next[w] == nullptr)
            next[w] = new Trie();
        
        count++;
        next[w]->revinsert(--word, ptr - 1);
    }
    
    int get(const char * word) {
        
        if(*word == '\0') return 1;
        if(*word == '?') return count;
        
        int w = *word - 'a';
        if(next[w] == nullptr) return 0;
        else return next[w]->get(++word);
    }
    
    int revget(const char * word, int ptr) {
        
        if(ptr < 0) return 1;
        if(*word == '?') return count;
        
        int w = *word - 'a';
        if(next[w] == nullptr) return 0;
        else return next[w]->revget(--word, ptr - 1);
    }
    
};

Trie * linear[100001];
Trie * rev[100001];


vector<int> solution(vector<string> words, vector<string> queries) {
    
    for(string word: words) {
        
        int size = word.size();
        
        if(linear[size] == nullptr) {
            linear[size] = new Trie();
        }
        if(rev[size] == nullptr) {
            rev[size] = new Trie();
        }
        
        linear[size]->insert(&word.front());
        rev[size]->revinsert(&word.back(), size - 1);
    }
    
    vector<int> answer;
    for(string query: queries) {
        
        int size = query.size();
        if(query.back() == '?') {
            if(linear[size] == nullptr) {
                answer.push_back(0);
                continue;
            }
            answer.push_back(linear[size] -> get(&query.front()));
        }
        else {
            if(rev[size] == nullptr) {
                answer.push_back(0);
                continue;
            }
            answer.push_back(rev[size] -> revget(&query.back(), size - 1));
        }
    }
    
    return answer;
}