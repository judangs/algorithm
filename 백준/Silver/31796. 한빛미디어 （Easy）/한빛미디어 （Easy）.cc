#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<int> book(N);
    for(int i=0; i<N; i++) cin >> book[i];

    sort(book.begin(), book.end());
    
    int answer = 1, mincost = book.front();
    for(auto cost: book) {
        if(mincost <= cost && cost < 2 * mincost) continue;
        mincost = cost;
        answer++;
    }

    cout << answer << endl;
    
}