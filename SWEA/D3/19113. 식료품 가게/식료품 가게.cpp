#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, N;

int main() {

    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    cin >> T;
    for(int k=1; k<=T; k++) {
        cin >> N;
        
        vector<long long> products(2 * N);

        long long item;
        for(int i=0; i<2*N; i++) {
            cin >> item;
            products[i] = item;
        }

        cout << "#" << k << " "; 
        for(long long product: products) {
            long long sales = product / 3 * 4;
            auto iter = find(products.begin(), products.end(), sales);
            if(iter != products.end()) {
                cout << product << " ";
                products.erase(iter);
            }
        }
        cout << endl;
    }
}
