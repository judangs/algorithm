#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int inf = 1e9;
int n, m;
string input, answer;

bool equals(char origin, char target) {
    if(origin == 'i') {
        if(target == 'i' || target == 'j' || target == 'l') return true;
        return false;
    }
    if(origin == 'v') {
        if(target == 'v' || target == 'w') return true;
        return false;
    }

    return (origin == target);
}

int calculate(int l, int r, vector<vector<int>> & cache) {

    if(l == n) return (m - r);
    if(r == m) return (n - l);

    int & ret = cache[l][r];
    if(ret != -1) return ret;
    
    ret = inf;
    if(equals(input[l], answer[r]))
        ret = min(ret, calculate(l + 1, r + 1, cache));
    else {
        ret = min(ret, 1 + calculate(l, r + 1, cache));
        ret = min(ret, 1 + calculate(l + 1, r, cache));
        ret = min(ret, 1 + calculate(l + 1, r + 1, cache));
    }

    return ret;
}

int main() {

    cin >> n >> m;
    cin >> input >> answer;

    vector<vector<int>> cache(n + 1, vector<int>(m + 1, -1));
    cout << calculate(0, 0, cache) << endl;
    
    
    
}