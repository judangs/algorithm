#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int K;
vector<int> eggs(4);
vector<vector<int>> answer;

struct Basket {
    int count;
    int index;
    
    bool operator<(const Basket & o) const {
        return count < o.count;
    }
};

void ordering(vector<int> & now) {

    vector<Basket> other;
    for(int idx=0; idx<4; idx++)
        other.push_back({ now[idx], idx });
    sort(other.begin(), other.end());

    if(!now[other[0].index] && !now[other[1].index] && !now[other[2].index])
        return;


    auto & target = now[other.back().index];

    int sum = other[0].count + other[1].count + other[2].count;
    if(sum % 2 == 1) {
        target--, now[other[2].index]--, now[other[1].index] += 2;
    }
    else {
        if(other[0].count + other[1].count < other[2].count) {
            if(now[other[1].index] == 0) {
                target--, now[other[2].index]--, now[other[1].index] += 2;
            }
            else {
                now[other[1].index]--, now[other[2].index]--, now[other[0].index] += 2;
            }
        }
        else {
            target += 2, now[other[2].index]--, now[other[1].index]--;
        }
    }

    answer.push_back(now);
    ordering(now);
}

int main() {

    cin >> K;
    for(auto & egg: eggs) cin >> egg;
    answer.push_back(eggs);

    ordering(eggs);
    for(auto ans: answer) {
        for(int count: ans) {
            cout << count << " ";
        }
        cout << "\n";
    }

}