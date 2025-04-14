#include <iostream>
#include <vector>

using namespace std;

int N, M, L, K;
int y, x;

struct Pos {
    int y;
    int x;
};

vector<Pos> stars;
int ans = 0;


int main() {
    cin >> N >> M >> L >> K;

    for(int i=0; i<K; i++) {
        cin >> x >> y;

        stars.push_back({y, x});
    }

    for(int i=0; i<K; i++) {
        for(int j=0; j<K; j++) {
            int cy = stars[i].y;
            int cx = stars[j].x;

            int count = 0;
            for(int k=0; k<K; k++) {
                if(cy <= stars[k].y && stars[k].y <= cy + L && cx <= stars[k].x && stars[k].x <= cx + L) {
                    count++;
                }
            }

            ans = max(ans, count);
        }
    }
    
    cout << (K - ans);

}