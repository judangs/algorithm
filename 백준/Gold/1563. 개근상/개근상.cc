#include <iostream>
#include <memory.h>

using namespace std;
typedef long long ll;

const int mod = 1000000;
int N;
ll cache[1001][2][3];

ll attendance(int day, int late, int cont) {

    if(day == N) return 1;

    ll & ret = cache[day][late][cont];
    if(ret != -1) return ret;

    ret = 0;

    ret = (ret + attendance(day + 1, late, 0)) % mod;
    if(late + 1 < 2)
        ret = (ret + attendance(day + 1, late + 1, 0)) % mod;
    if(cont + 1 < 3)
        ret = (ret + attendance(day + 1, late, cont + 1)) % mod;
    
    return ret;
}

int main() {
    
    memset(cache, -1, sizeof(cache));
    
    cin >> N;
    cout << attendance(0, 0, 0) << endl;

}