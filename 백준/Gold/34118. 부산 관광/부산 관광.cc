#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
string A, B;

const int inf = 1e9;
vector<int> price(4);

int skip[4] = { 1, 3, 5, 4 };
int cache[2001][2001];

int tour(int han, int jung) {

    if(han >= N && jung >= N) return 0;

    int & ret = cache[han][jung];
    if(ret != -1) return ret;
    
    ret = inf;
    
    if(han < N && jung < N) {
        bool needA = (A[han] == '1');
        bool needB = (B[jung] == '1');
        
        if(!needA && !needB) {
            ret = min(ret, tour(han + 1, jung + 1));
        }
        else if(needA && needB) {

            if(han == jung) {
                ret = min(ret, tour(han + 4, jung + 4) + price[3]);
            }
            
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 3; j++) {
                    ret = min(ret, tour(han + skip[i], jung + skip[j]) + price[i] + price[j]);
                }
            }
        }
        else if(needA && !needB) {

            if(han == jung) {
                ret = min(ret, tour(han + 4, jung + 4) + price[3]);
            }

            for(int i = 0; i < 3; i++) {
                ret = min(ret, tour(han + skip[i], jung + 1) + price[i]);
            }
        }
        else if(!needA && needB) {

            if(han == jung) {
                ret = min(ret, tour(han + 4, jung + 4) + price[3]);
            }

            for(int i = 0; i < 3; i++) {
                ret = min(ret, tour(han + 1, jung + skip[i]) + price[i]);
            }
        }
    }
    else if(han < N) {
        if(A[han] == '1') {
            for(int i = 0; i < 3; i++) {
                ret = min(ret, tour(han + skip[i], jung) + price[i]);
            }
        } else {
            ret = min(ret, tour(han + 1, jung));
        }
    }
    else if(jung < N) {
        if(B[jung] == '1') {
            for(int i = 0; i < 3; i++) {
                ret = min(ret, tour(han, jung + skip[i]) + price[i]);
            }
        } else {
            ret = min(ret, tour(han, jung + 1));
        }
    }

    return ret;
}

int main() {
    cin >> N;
    cin >> A >> B;
    for(int & p: price) cin >> p;

    memset(cache, -1, sizeof(cache));

    int answer = tour(0, 0);
    cout << answer << endl;

}