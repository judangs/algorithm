#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int T, l, n;

int main() {
    
    cin >> T;
    while(T--) {

        cin >> l >> n;

        vector<int> ant(n);
        for(int i=0; i<n; i++) cin >> ant[i];

        sort(ant.begin(), ant.end());

        int maxt = 0, mint = 0;
        
        for(auto p: ant) {
            mint = max(mint, min(p, l - p));
            maxt = max(maxt, max(p, l - p));
        }


        cout << mint << " " << maxt << "\n";
    }
}