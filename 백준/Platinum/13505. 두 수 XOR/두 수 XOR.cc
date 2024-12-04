#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define BITSIZE 30

using namespace std;

struct Trie {
    Trie * next[2];
    
    Trie() {
        for(int idx=0; idx<2; idx++) {
            next[idx] = nullptr;
        }
    }
    
    void insert(string bin, int ptr) {
        if(bin.size() == ptr)
            return;
        
        int cur = bin[ptr] - '0';
        if(next[cur] == nullptr) {
            next[cur] = new Trie();
        }
        
        next[cur]->insert(bin, ptr + 1);
    }
    
    int find(string bin, int ptr, int ret) {
        
        if(bin.size() == ptr)
            return ret;
            
        int cur = bin[ptr] - '0'; 
        int xcur = !cur;
        
        if(next[xcur] != nullptr) 
            return next[xcur]->find(bin, ptr + 1, ret | (1 << (BITSIZE - ptr)));
        else 
            return next[cur]->find(bin, ptr + 1, ret);            
    }
};

int N, A;

Trie * root = new Trie();
vector<string> arr;

string int_to_str_bin(int decimal) {
    string bin = "";
    int shift = BITSIZE;
    while(0 <= shift) {
        bin += (((1 << shift) & decimal) == 0) ? '0' : '1';
        shift--;
    }
    
    return bin;
}

int main() {
    
    cin >> N;
    for(int idx=0; idx<N; idx++) {
        cin >> A;
        arr.push_back(int_to_str_bin(A));
        root->insert(arr.back(), 1);
    }
    
    int answer = 0;
    for(string bin: arr) {
        answer = max(answer, root->find(bin, 1, 0));
    }
    
    cout << answer;
}