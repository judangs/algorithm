#include <iostream>
#include <cmath>
#include <algorithm>

#define INF 1000000

using namespace std;

int N, M;
bool broken[10] = {false, };

bool available(int channel) {

    if(channel == 0) return (broken[channel] == false);

    while(channel) {
        if(broken[channel % 10]) return false;
        channel /= 10;
    }

    return true;
}

int calculate(int channel) {

    if(channel == 0) return (1 + abs(channel - N));

    int count = 0, now = channel;
    while(now) {
        now /= 10, count++;
    }

    int click = count + abs(channel - N);
    return click;
}

int main() {

    cin >> N >> M;

    int unique = 0;
    for(int i=0; i<M; i++) {
        int num; cin >> num;
        broken[num] = true; unique++;
    }

    int answer = abs(N - 100);
    for(int channel=0; channel < INF; channel++) {
        if(available(channel))
            answer = min(answer, calculate(channel));
    }

    cout << answer << endl;
    
}