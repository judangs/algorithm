#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define INF 2e9

using namespace std;

int N;
vector<int> snow;

int main() {

    cin >> N;
    snow = vector<int>(N);
    for(auto & H: snow) cin >> H;

    sort(snow.begin(), snow.end());

    int answer = INF;
    for(int i = 0; i < N - 1; i++) {
        for(int j = i + 1; j < N; j++) {
            int lo = i + 1, hi = j - 1;
            while(lo < hi) {
                int s1 = snow[i] + snow[j];
                int s2 = snow[lo] + snow[hi];
                
                answer = min(answer, abs(s1 - s2));
                
                if(s1 < s2) hi--;
                else lo++;
            }
        }
    }

    cout << answer << endl;


}