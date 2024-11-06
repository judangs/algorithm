#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Trie {
    
    Trie * next[26];
    int route;
    int depth;
    
    Trie(int d) {
        
        route = 0;
        depth = d;
        
        for(int idx=0; idx<26; idx++) {
            next[idx] = nullptr;
        }
    }
};


void insert(Trie * root, string node) {
    
    Trie * current = root;
    for(auto & c: node) {
        
        int idx = c - 'a';
        if(current->next[idx] == nullptr) {
            current->next[idx] = new Trie(current->depth + 1);
        }
        
        current->next[idx]->route++;
        current = current->next[idx];
    }
}

int find(Trie * root, string node) {
    
    Trie * current = root;
    for(int index=0; index<node.size(); index++) {
        int idx = node[index] - 'a';
        current = current->next[idx];
    
        if(current->route == 1) {
            return (current->depth);
        }
        
    }
    return node.size();
}

Trie * root = new Trie(0);

int solution(vector<string> words) {
    
    for(string word: words) {
        insert(root, word);
    }
    
    int answer = 0;
    for(string word: words) {
        answer += find(root, word);
    }
    
    return answer;
}