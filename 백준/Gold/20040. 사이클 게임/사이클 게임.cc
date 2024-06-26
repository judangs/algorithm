#include <iostream>
#include <vector>

using namespace std;

int N, M, a, b;
vector<int> parent;

int find(int start) {
    if(start == parent[start])
        return start;
    return find(parent[start]);
}

int main() {
    cin >> N >> M;
    
    parent.resize(N);
    for(int i=0; i<N; i++) {
        parent[i] = i;
    }

    
    for(int i=0; i<M; i++) {
        cin >> a >> b;

        a = find(a);
        b = find(b);
        if(a == b) {
            cout << i + 1;
            return 0;
        }
        else {
            if(a < b) parent[b] = a;
            else parent[a] = b;
        }
    }

    cout << "0";

    
    
}