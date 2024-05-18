#include <iostream>

using namespace std;

int T, D, L, N;

int damage = 0;

void dfs(int depth) {
    if(depth == N) return;
    
    dfs(depth + 1);
    damage += D / 100 * (100 + depth * L);
}

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        cin >> D >> L >> N;
        
        dfs(0);
        cout << "#" << k << " ";
        cout << damage << endl;
        damage = 0;
    }
}