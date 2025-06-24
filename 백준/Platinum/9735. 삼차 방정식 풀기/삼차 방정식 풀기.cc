#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

#define INFANS 1000000

using namespace std;
typedef long double ld;

int N;


vector<ld> calculate(vector<ld> & poly) {
    
    vector<ld> ans;
    auto a = poly[0], b = poly[1], c = poly[2];

    if(fabsl(a) < 1e-10) {
        if(fabsl(b) < 1e-10) return ans;
        else return {-c / b};
    }

    ld d = pow(b, 2) - 4 * a * c;
    if(d > 1e-10) {
        ans.push_back((-b + sqrt(d)) / (2.0 * a));
        ans.push_back((-b - sqrt(d)) / (2.0 * a));
    }
    else if(fabsl(d) < 1e-10) ans = {-b / (2 * a)};

    sort(ans.begin(), ans.end());
    return ans;
}

vector<ld> differentiate(vector<ld> & poly) {
    vector<ld> ret;
    for(int i=0; i<poly.size() - 1; i++) {
        ret.push_back(poly[i] * (poly.size() - 1 - i));
    }
    return ret;
}

ld f(vector<ld> & poly, ld x) {
    ld ret = 0.0;
    for(int i=0; i<poly.size(); i++) {
        ret += poly[i] * pow(x, poly.size() - 1 - i);
    }
    return ret;
}

vector<ld> solved(vector<ld> & poly) {
    if(poly.size() <= 3) return calculate(poly);

    vector<ld> differential = differentiate(poly);
    vector<ld> sol = solved(differential);
    
    sol.insert(sol.begin(), -INFANS - 1); sol.insert(sol.end(), INFANS + 1);

    set<ld> ans;
    for(int i=0; i<sol.size() - 1; i++) {
        auto x1 = sol[i], x2 = sol[i + 1];
        ld y1 = f(poly, x1), y2 = f(poly, x2);

        if(fabsl(y1) < 1e-10) ans.insert(x1);
        if(fabsl(y2) < 1e-10) ans.insert(x2);

        if(1e-10 < y1 * y2) continue;
        if(fabsl(y1) < 1e-10 || fabsl(y2) < 1e-10) continue;
        if(f(poly, x1) > f(poly, x2)) swap(x1, x2);
        
        for(int i=0; i<100; i++) {
            ld mx = (x1 + x2) / 2.0;
            if(f(poly, mx) * f(poly, x1) <= 0) x2 = mx;
            else x1 = mx;            
        }

        if(fabs((x1 + x2) / 2.0) < 1e-10) ans.insert(0.0);
        else 
            ans.insert((x1 + x2) / 2.0);
    }

    return vector<ld>(ans.begin(), ans.end());
}

int main() {

    cin >> N;
    while(N--) {
        vector<ld> poly(4);    
        for(int i=0; i<4; i++) cin >> poly[i];

        vector<ld> answer = solved(poly);
        
        cout << fixed << setprecision(4);
        for(auto ans: answer) {
            if(fabs(ans) < 1e-10) cout << "0.0000 ";
            else cout << ans << " ";
        }
        cout << "\n";
    }
    
}
