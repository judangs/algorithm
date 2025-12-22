#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int N;
vector<pair<char, int>> cows;

int count(long long pos) {
    int liars = 0;
    for(const auto& [comp, p] : cows) {
        if(comp == 'L' && pos > p) liars++;
        if(comp == 'G' && pos < p) liars++;
    }
    return liars;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> N;
    cows.resize(N);
    set<long long> candidates;
    
    for(auto& [comp, p] : cows) {
        cin >> comp >> p;
        candidates.insert(p);
    }
    
    int answer = N;
    for(long long pos : candidates) {
        answer = min(answer, count(pos));
    }
    
    cout << answer << endl;

}