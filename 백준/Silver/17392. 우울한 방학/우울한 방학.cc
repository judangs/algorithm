#include <iostream>
#include <vector>

using namespace std;

int N, M;

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    int total = 0;
    for(int i=1; i<=N; i++) {
        int happy; cin >> happy;
        total += (happy + 1);
    }

    if(total >= M) cout << "0" << endl;
    else {
        vector<int> day(N + 1, 0);
        for(int p = 0, sad = (M - total); sad > 0; sad--, p++) {
            day[p % (N + 1)]++;
        }

        int answer = 0;
        for(auto & count: day) {
            while(count) {
                answer += (count * count);
                count--;
            }
        }

        cout << answer << endl;
    }
}