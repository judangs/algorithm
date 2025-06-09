#include <iostream>
#include <vector>
#include <unordered_map>

#define MAXVALUE 200000

using namespace std;

unordered_map<int, pair<int, int>> twosum;
vector<int> arr;

int w, n, a;

int main() {
    
    cin >> w >> n;
    for(int i=0; i<n; i++) {
        cin >> a;
        arr.push_back(a);
    }

    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            int sum = arr[i] + arr[j];
            twosum[sum] = {i, j};
        }
    }

    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            int remain = w - (arr[i] + arr[j]);
            if(0 <= remain && remain <= 2 * MAXVALUE) {
                auto iter = twosum.find(remain);    
                if(iter != twosum.end() && iter->second.first != i && iter->second.second != i && iter->second.first != j && iter->second.second != j) {
                    cout << "YES";
                    return 0;
                }
            }
        }
    }

    cout << "NO";
}