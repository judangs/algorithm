#include <iostream>
#include <vector>
#include <cmath>
#include <memory.h>

using namespace std;

struct Cloth {
    int lo, hi, fancy;
};

int D, N, T, A, B, C;

int cache[201][201];

vector<int> temperature;
vector<Cloth> clothes;

int main() {

    memset(cache, 0, sizeof(cache));

    cin >> D >> N;
    for(int i=0; i<D; i++) {
        cin >> T; temperature.push_back(T);
    }

    for(int i=0; i<N; i++) {
        cin >> A >> B >> C; clothes.push_back({A, B, C});
    }

    for(int day=1; day<D; day++) {
        for(int before=0; before<N; before++) {

            auto weared = clothes[before];
            if(weared.lo <= temperature[day - 1] && temperature[day - 1] <= weared.hi) {
                for(int after=0; after<N; after++) {

                    auto wear = clothes[after];
                    if(wear.lo <= temperature[day] && temperature[day] <= wear.hi) {
                        cache[day][after] = max(cache[day][after], cache[day - 1][before] + abs(wear.fancy - weared.fancy));
                    }
                }
            }
        }
    }

    int answer = 0;
    for(int idx=0; idx<N; idx++) answer = max(answer, cache[D - 1][idx]);
    cout << answer;
}