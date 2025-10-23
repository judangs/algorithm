#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int compare(string a, string b) {
    
    int ret = 1, now = 0;
    for(int i = 0; i < 4; i++) {
        now += pow((a[i] - '0') - (b[i] - '0'), 2);
    }

    ret *= now; now = 0;
    for(int i = 4; i < 6; i++) {
        now += pow((a[i] - '0') - (b[i] - '0'), 2);       
    }
    ret *= now; now = 0;
    for(int i = 6; i < 8; i++) {
        now += pow((a[i] - '0') - (b[i] - '0'), 2);
    }

    ret *= now;
    return ret;
}

int main() {

    string birth; cin >> birth;
    int N; cin >> N;

    vector<string> date(N);
    for(auto & day: date) cin >> day;
    sort(date.begin(), date.end());

    int hi = 0; string answer = "";
    for(auto & day: date) {
        int now = compare(day, birth);
        if(now > hi) {
            hi = now, answer = day;
        }
    }

    cout << answer << endl;
    

}