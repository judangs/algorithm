#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define BITSIZE 30

using namespace std;

int T, N, A;

struct Trie {
    Trie * next[2];
    
    Trie() {
        for(int idx=0; idx<2; idx++) {
            next[idx] = nullptr;
        }
    }
    
    void insert(int bin, int ptr) {
        if(ptr < 0) return;
        
        int cur = (bin >> ptr) & 1;
        if(next[cur] == nullptr) next[cur] = new Trie();
        
        next[cur]->insert(bin, ptr - 1);
    }
    
    int find(int bin, int ptr, int xcost) {
        if(ptr < 0)
            return xcost;
        
        int cur = (bin >> ptr) & 1;
        int xcur = !cur;
        
        if(next[xcur] != nullptr)
            return next[xcur]->find(bin, ptr - 1, xcost | (1 << ptr));
        else
            return next[cur]->find(bin, ptr - 1, xcost);
    }
};

int main() {
    cin >> T;
    while(T--) {
        
        cin >> N;
        vector<int> arr(N);
        for(int idx=0; idx<N; idx++) {
            cin >> arr[idx];
        }
        
        vector<int> prexor;
        prexor.push_back(0);
        for(int idx=0; idx<N; idx++) {
            prexor.push_back(prexor.back() ^ arr[idx]);
        }
        
        Trie * root = new Trie();
        for(int bin: prexor) {
            root->insert(bin, BITSIZE);
        }
        
        int answer = 0;
        for(int bin: prexor) {
            answer = max(answer, root->find(bin, BITSIZE, 0));
        }
        
        cout << answer << "\n";
    }
}