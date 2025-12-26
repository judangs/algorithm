#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define MAX_K 100000
using namespace std;

int K;
vector<bool> is_prime(MAX_K + 1, true);
vector<pair<int, int>> selected;

struct Node {
    int depth;
    int now;
    int leaf;
    int count;
};

void build_prime_tbl() {

    is_prime[1] = false;
    for(int i = 2; i < MAX_K + 1; i++) {
        for(int j = i; j < MAX_K + 1; j += i) {
            if(j > i) is_prime[j] = false;
        }
    }
}

void select(int dep, int A, int B, vector<int> & div) {
    if(dep == div.size()) {
        selected.push_back({ A, B });
        return;
    }

    select(dep + 1, A * div[dep], B, div);
    select(dep + 1, A, B * div[dep], div);
}

int main() {

    cin >> K;
    build_prime_tbl();

    if(is_prime[K]) {
        cout << (K + 1) << "\n";
        for(int node = 1; node <= K; node++) cout << node << " " << (node + 1) << "\n";
    }
    else {
        vector<int> div;
        int now = K;
        for(int num = 2; num < K; num++) {
            if(is_prime[num]) {
                while(now % num == 0) {
                    now /= num;
                    div.push_back(num); 
                }
            }
        }

        select(0, 1, 1, div);
        selected.push_back({ 1, K });
        sort(selected.begin(), selected.end(), [](const pair<int, int> & l, const pair<int, int> & r) {
            return l.first + l.second < r.first + r.second;
        });

        int A, B;
        tie(A, B) = selected.front();
        if(A > B) swap(A, B);
        
        cout << (A + B) << "\n";
        for(int node = 1; node < B; node++) cout << node << " " << (node + 1) << "\n";
        for(int node = B, count = 1; 0 < node && 0 < A; node--) {
            cout << node << " " << (B + count++) << "\n";
            A--;
        }
        
    }

}