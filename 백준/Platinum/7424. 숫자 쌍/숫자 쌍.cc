#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int N;
int p = 0;

int number[12];
int x[12], y[12];

struct Expression {
    int x;
    int y;
    
    bool operator<(const Expression & o) const {
        return x < o.x;
    }
};
set<Expression> answer;


void check() {

    y[p - 1] = 0;

    int x1 = 0, y1 = 0;
    for(int place=0, ex = 1; place<p; place++, ex *= 10) {
        x1 += (x[place] * ex);
        y1 += (y[place] * ex);
    }

    if(x1 + y1 == N && x1 != y1 && x1 >= 10 && y1 >= 0) answer.insert({x1, y1});
}

void backtracking(int place, int skip, int carry) {
    
    if(place == p) {
        if(skip && 0 == carry) check();
        return;
    }

    for(x[place + 1] = 0; x[place + 1] < 10; x[place + 1]++) {
        if(!skip) {
            y[place] = x[place];
            int k = y[place] + x[place] + carry;
            if(k % 10 == number[place]) backtracking(place + 1, skip, k / 10);
        }

        y[place] = (place + 1 == p ? 0 : x[place + 1]);
        int k = y[place] + x[place] + carry;
        if(k % 10 == number[place]) backtracking(place + 1, skip + 1, k / 10);        
    }
}

int convert(int a, int b) {
    int l = 0, r = (b == 0 ? 1 : 0);
    while(a) l++, a /= 10;
    while(b) r++, b /= 10;

    return max(0, (l - r - 1));
}

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> N;

    int nn = N;
    while(nn) {
        number[p++] = nn % 10;
        nn /= 10; 
    }

    for(x[0] = 0; x[0] < 10; x[0]++) {
        backtracking(0, 0, 0);
    }

    cout << answer.size() << "\n";
    for(auto ans: answer) {
        int zero = convert(ans.x, ans.y);
        cout << ans.x << " + ";
        while(zero--) cout << '0';
        cout << ans.y << " = " << N << "\n";
    }
}
