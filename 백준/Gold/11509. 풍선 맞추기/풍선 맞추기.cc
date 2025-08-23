#include <iostream>

using namespace std;

int N;
int balloon[1000000];
int exist[1000000];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for(int i=0; i<N; i++) cin >> balloon[i];
    
    int arrow = 1, now = balloon[0];
    for(int i=0; i<N; i++) {
        if(now == balloon[i]) now--;
        else {
            if(exist[balloon[i]]) {
                exist[balloon[i]]--;
                if(0 <= balloon[i] - 1) exist[balloon[i] - 1]++;
            }
            else {
                arrow++;
                exist[now]++;
                now = balloon[i] - 1;
            }
        }
    }

    cout << arrow << endl;

}