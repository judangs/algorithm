#include <iostream>

using namespace std;

const int maxrobot = 1e6 + 1;
int parent[maxrobot];
int robot[maxrobot];

int N;

int find(int part) {
    if(parent[part] == part) return part;
    return (parent[part] = find(parent[part]));
}

void merge(int a, int b) {
    a = find(a);  b = find(b);
    
    if(a != b) {
        if(a > b) swap(a, b);
        parent[b] = a;
        robot[a] += robot[b];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    
    for(int i = 1; i < maxrobot; i++) {
        parent[i] = i;
        robot[i] = 1;
    }

    while(N--) {
        char type; 
        cin >> type;
        if(type == 'I') {
            int a, b; cin >> a >> b;
            merge(a, b);
        }
        else {
            int c; cin >> c;
            cout << robot[find(c)] << "\n";
        }
    }
}