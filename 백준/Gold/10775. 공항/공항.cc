#include <iostream>
#include <vector>

using namespace std;

int G, P, g;
vector<int> parent;

int find(int start) {
    if(start == parent[start])
        return start;
    return (parent[start] = find(parent[start]));
}

int main() {
    cin >> G;
    cin >> P;

    parent.resize(G + 1);
    for(int i=0; i<G+1; i++) parent[i] = i;

    int current = 0;
    for(current; current <= P; current++) {
        cin >> g;

        int gate = find(g);
        if(gate == 0) break;

        parent[gate] = gate - 1;
    }

    cout << current;
}