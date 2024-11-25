#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Trie {
    
    Trie * next[10];
    
    Trie() {
        for(int idx=0; idx<10; idx++) {
            next[idx] = nullptr;
        }
    }
    
    void insert(const char * cur) {
        if(*cur == '\0') return;
        
        int num = *cur - '0';
        if(next[num] == nullptr)
            next[num] = new Trie();
        
        next[num]->insert(++cur);
    }
    
    bool check(const char * cur) {
        if(*cur == '\0') {
            for(int idx=0; idx<10; idx++) {
                if(next[idx] != nullptr) {
                    return false;
                }
            }
            
            return true;
        }
        
        int num = *cur - '0';
        return next[num]->check(++cur);
    }
};

int T, N;

bool compare(string a, string b) {
    return a.size() < b.size();
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> T;
    
    while(T--) {
        
        Trie * trie = new Trie();
        vector<string> numbers;
        
        cin >> N;
        string number;
        
        for(int idx=0; idx<N; idx++) {
            cin >> number;
            numbers.push_back(number);
        }
        
        sort(numbers.begin(), numbers.end(), compare);
        for(string number: numbers) {
            trie->insert(&number.front());
        }
        
        bool flag = true;
        for(string number: numbers) {
            if(trie->check(&number.front()) == false) {
                flag = false;
                break;
            }
        }
        
        if(flag == true) cout << "YES\n";
        else cout << "NO\n";
    }
    
}