#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int T;
vector<int> unit = {60, 10, 1};

void calculate(int d, int now, int count, vector<int> click, map<vector<int>, int> & answer) {
    if(d == 3) {
        answer[click] = count;
        return;
    } 

    int abs_now = abs(now);
    
    int plus, minus;
    if(d == 0) { plus = 0; minus = 2; }
    else if(d == 1) { plus = 1; minus = 2; }
    else { plus = 3; minus = 4; }
    
    vector<int> click1 = click;
    if(now >= 0) {
        click1[plus] = now / unit[d];
        calculate(d + 1, now - unit[d] * click1[plus], count + click1[plus], click1, answer);
    } else {
        click1[minus] = abs_now / unit[d];
        calculate(d + 1, now + unit[d] * click1[minus], count + click1[minus], click1, answer);
    }
    
    vector<int> click2 = click;
    if(now >= 0) {
        click2[plus] = now / unit[d] + 1;
        calculate(d + 1, now - unit[d] * click2[plus], count + click2[plus], click2, answer);
    } else {
        click2[minus] = abs_now / unit[d] + 1;
        calculate(d + 1, now + unit[d] * click2[minus], count + click2[minus], click2, answer);
    }
}

bool is_greater(const vector<int> & l, const vector<int> & r) {
    for(int i = 0; i < 5; i++) {
        if(l[i] != r[i]) {
            return l[i] < r[i];
        }
    }
    return false;
}

int main() {
    cin >> T;
    while(T--) {
        int N; 
        cin >> N;
        vector<int> ret(5, 0); 
        map<vector<int>, int> answer;
        calculate(0, N, 0, ret, answer);

        int minclick = 1e9;
        vector<int> best_result(5, 0);
        
        for(auto iter = answer.begin(); iter != answer.end(); ++iter) {
            if(iter->second < minclick || 
               (iter->second == minclick && is_greater(iter->first, best_result))) {
                best_result = iter->first;
                minclick = iter->second;
            }
        }
        
        for(int i = 0; i < 5; i++) {
            cout << best_result[i];
            if(i < 4) cout << " ";
        }
        cout << endl;
    }
}