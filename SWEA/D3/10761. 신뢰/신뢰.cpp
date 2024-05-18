#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int T, N;
int current_time = 0;

struct robot {
    int time = 0;
    int current = 1;
};

void move(robot & r, int next) {
    if(r.time + abs(next - r.current) == current_time) {
        r.time += abs(next - r.current) + 1;
        r.current = next;
        current_time = r.time;
    }
    else {
        if(r.time + abs(next - r.current) < current_time) {
            current_time++;
            r.time = current_time;
            r.current = next;
        }
        else {
            current_time += abs(next - r.current) - (current_time - r.time) + 1;
            r.time = current_time;
            r.current = next;
        }
    }
}

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        cin >> N;

        robot orange;
        robot blue;

        char type;
        int button;
        for(int i=0; i<N; i++) {
            cin >> type >> button;
            if(type == 'O') move(orange, button);
            else move(blue, button);
        }

        cout << "#" << k << " ";
        cout << current_time << endl;
        current_time = 0;
    }
}