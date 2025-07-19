#include <iostream>
#include <vector>

using namespace std;

int N, M;

struct Part {
    int idx, count;
};
vector<Part> assembly[101];
vector<vector<int>> need(101, vector<int>(101, 0));
vector<bool> basic(101, true);
vector<bool> visited(101, false);

void calculate(int now) {

    if(visited[now]) return;
    if (basic[now]) {
        need[now][now] = 1;
        return;
    }

    visited[now] = true;

    for (auto next : assembly[now]) {
        calculate(next.idx);
        for (int i = 1; i <= N; i++) {
            need[now][i] += need[next.idx][i] * next.count;
        }
    }
}

int main() {

    cin >> N;
    cin >> M;

    for(int i=0; i<M; i++) {
        int X, Y, K; cin >> X >> Y >> K;
        basic[X] = false;
        assembly[X].push_back({Y, K});
    }

    calculate(N);
    for(int i=1; i<=N; i++) {
        if(basic[i])
            cout << i << " " << need[N][i] << "\n";
    }

}