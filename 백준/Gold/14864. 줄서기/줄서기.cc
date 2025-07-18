#include <iostream>
#include <vector>
#include <queue>

#define MAXSTUDENT 100001

using namespace std;

int N, M;


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    vector<int> card(N + 1);
    for(int i=1; i<=N; i++) card[i] = i;

    for(int i=0; i<M; i++) {
        int X, Y; cin >> X >> Y;
        card[X]++, card[Y]--;
    }

    vector<bool> visit(N + 1, false);
    for(int i=0; i<N; i++) {
        if(visit[card[i]] || card[i] < 0 || card[i] > N) {
            cout << "-1" << endl;
            return 0;
        }
        visit[card[i]] = true;
    }

    for(int i=1; i<=N; i++) cout << card[i] << " ";
    
}