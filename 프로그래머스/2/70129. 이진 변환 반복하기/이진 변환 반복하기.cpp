#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string translation(int n) {
    string ret = "";
    while(n != 1) {
        ret += to_string(n % 2);
        n /= 2;
    }

    ret += "1";
    reverse(ret.begin(), ret.end());
    return ret;
}

vector<int> solution(string s) {
    int remove_zero = 0;
    int count = 0;
    
    while(s.size() != 1 || stoi(s) != 1) {
        int idx;
        while((idx = s.find("0")) != string::npos) {
            s.erase(idx, 1);
            remove_zero++;
        }

        s = translation(s.size());
        count++;
    }
    cout << count << " " << remove_zero << endl;
    return {count, remove_zero};
}