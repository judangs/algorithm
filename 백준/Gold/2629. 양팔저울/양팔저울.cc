#include <iostream>
#include <cmath>

using namespace std;

int N, M;

int weight[31];
int bead[7];
bool dp[31][40001];

int main() {

    cin >> N;
    for(int i=1; i<=N; i++) cin >> weight[i];
    cin >> M;
    for(int i=1; i<=M; i++) cin >> bead[i];


    dp[0][0] = true;
    for(int idx=1; idx<=N; idx++)
        for(int w=0; w <= 40000; w++)
            dp[idx][w] = dp[idx - 1][w] | dp[idx - 1][w + weight[idx]] | dp[idx - 1][abs(w - weight[idx])];


    for(int i=1; i<=M; i++) {
        bool answer = false;
        for(int idx=1; idx<=N; idx++)
            if(dp[idx][bead[i]])
                answer = true;

        if(answer) cout << "Y" << " ";
        else cout << "N" << " ";
    }

    cout << endl;

}