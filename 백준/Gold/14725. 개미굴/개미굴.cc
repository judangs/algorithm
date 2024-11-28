#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>


using namespace std;

int N, K, t;

struct Trie {
    map<string, Trie *> next;
    string cur;
    
    Trie() {}
    
    void insert(vector<string> arr, int ptr) {
        
        cur = arr[ptr];
        if(ptr == arr.size() - 1)
            return;
        
        string feed = arr[ptr + 1];
        if(next.find(feed) == next.end()) {
            next[feed] = new Trie();
        }
        
        
        next[feed]->insert(arr, ptr + 1);
    }
    
    void get(int depth) {
        
        cout << string(2 * depth, '-') + cur << endl;
        if(next.size() == 0) {
            return;
        }
        
        for(auto iter=next.begin(); iter!=next.end(); iter++) {
            iter->second->get(depth + 1);
        }
    }
};

map<string, Trie *> startNode;

int main() {
    cin >> N;
    
    for(int idx=0; idx<N; idx++) {
        cin >> K;
        
        vector<string> arr(K);
        for(int k=0; k<K; k++) {
            cin >> arr[k];
        }
        
        if(startNode.find(arr.front()) == startNode.end()) {
            startNode[arr.front()] = new Trie();
        }
        
        startNode[arr.front()]->insert(arr, 0);
    }
    
    for(auto iter=startNode.begin(); iter!=startNode.end(); iter++) {
        iter->second->get(0);
    }
}