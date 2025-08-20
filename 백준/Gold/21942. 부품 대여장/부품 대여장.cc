#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <numeric>

using namespace std;
typedef long long ll;

ll N, F;
string L;


struct Parser {

    vector<int> monthly = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int operator()(string period) {
        int day = stoi(period.substr(0, 3));
        int hour = stoi(period.substr(4, 2));
        int minute = stoi(period.substr(7, 2));
        return 24 * 60 * day + 60 * hour + minute;
    }

    int operator()(string today, string now) {
        int month = stoi(today.substr(5, 7));
        int day = stoi(today.substr(8, 2));

        int hour = stoi(now.substr(0, 2));
        int minute = stoi(now.substr(3, 2));
        
        return (accumulate(monthly.begin(), monthly.begin() + month, 0) + day) * 24 * 60 + 60 * hour + minute;
    }

}parser;

map<pair<string, string>, int> memo;
map<string, ll> answer;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> L >> F;
    int period = parser(L);

    for(int i=0; i<N; i++) {
        string today, now, part, name; cin >> today >> now >> part >> name;

        auto key = make_pair(name, part);
        
        if(memo.find(key) == memo.end()) {
            memo[key] = parser(today, now);
        }
        else {
            int time = parser(today, now) - memo[key];
            if(period < time)
                answer[name] += (time - period) * F;

            memo.erase(key);
        }
    }

    if(answer.empty()) {
        cout << "-1" << "\n";
    }
    else {
        for(auto & [name, fine]: answer) {
            cout << name << " " << fine << "\n";
        }
    }

}