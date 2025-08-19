#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

int N, Price;
vector<int> item[4];


double calculate(int i, int j, int k) {
    
    double cost = 0.0, now = Price;
    for(int ii=0; ii<i; ii++) {
        cost += item[1][ii];
        now *= 0.99;
    }
    for(int jj=0; jj<j; jj++) {
        cost += item[2][jj];
        now *= 0.98;
    }
    for(int kk=0; kk<k; kk++) {
        cost += item[3][kk];
        now *= 0.97;
    }

    return (now + cost);
}

int main() {

    cin >> N >> Price;

    for(int i=0; i<N; i++) {
        int C, P; cin >> C >> P;
        item[P].push_back(C);
    }

    for(int percent=1; percent<=3; percent++) {
        sort(item[percent].begin(), item[percent].end());
    }

    double answer = Price;
    
    for(int i=0; i<=item[1].size(); i++) {
        for(int j=0; j<=item[2].size(); j++) {
            for(int k=0; k<=item[3].size(); k++) {
                answer = min(answer, calculate(i, j, k));
            }
        }
    }

    cout << fixed << setprecision(6);
    cout << answer << endl;

}