#include <iostream>
#include <vector>

using namespace std;

int T, N, M;

int main() {
    cin >> T;
    for(int k=1; k<=T; k++) {
        cin >> N >> M;

        vector<int> snack(N);

        int value;
        for(int i=0; i<N; i++) {
            cin >> value; 
            snack[i] = value;
        }

        int result = 0;
        for(int i=0; i<N; i++) {
            for(int j=i+1; j<N; j++) {
                int sum = snack[i] + snack[j];
                if(result < sum && sum <= M) {
                    result = sum;
                }
            }
        }

        cout << "#" << k << " ";
        cout << (result == 0 ? -1: result) << endl;
    }
}