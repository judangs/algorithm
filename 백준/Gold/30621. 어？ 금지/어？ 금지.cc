#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int N;
struct Sound {
    int time, before;
    ll confusion;

    bool operator<(const Sound & o) const {
        return time < o.time;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<Sound> sounds(N);
    for(int i=0; i<N; i++) cin >> sounds[i].time;
    for(int i=0; i<N; i++) cin >> sounds[i].before;
    for(int i=0; i<N; i++) cin >> sounds[i].confusion;

    vector<ll> confusion(N);
    confusion[0] = sounds[0].confusion;
    for(int idx=1; idx<N; idx++) {

        int end = sounds[idx].time, start = end - sounds[idx].before - 1;
        auto iter = upper_bound(sounds.begin(), sounds.begin() + idx, Sound{start, -1, -1});
        
        if(iter != sounds.begin()) {
            int ptr = --iter - sounds.begin();
            sounds[idx].confusion += confusion[ptr];
        }

        confusion[idx] = max(confusion[idx - 1], sounds[idx].confusion);
    }    

    ll answer = confusion.back();
    cout << answer << endl;

}