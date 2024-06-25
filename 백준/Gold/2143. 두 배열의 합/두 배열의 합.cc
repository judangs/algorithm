#include <iostream>
#include <vector>
#include <map>

using namespace std;

int N, M, a, b;
long long T;
vector<long long> A, B;


void get_prefix(map<long long, long long> & prefix, vector<long long> & arr) {

    vector<vector<long long>> r(arr.size(), vector<long long>(arr.size()));

    for(int i=0; i<arr.size(); i++) {
        r[i][i] = arr[i];
        prefix[r[i][i]]++;
    }

    for(int i=0; i<arr.size() - 1; i++) {
        r[i][i + 1] = arr[i] + arr[i + 1];
        prefix[r[i][i + 1]]++;
    }

    for(int k=2; k<arr.size(); k++) {
        for(int start=0; start+k<arr.size(); start++) {
            int end = start + k;
            r[start][end] = r[start][end - 1] + arr[end];
            prefix[r[start][end]]++;
        }
    }
}

long long solve() {

    map<long long, long long> prefix_A, prefix_B;
    get_prefix(prefix_A, A);
    get_prefix(prefix_B, B);

    long long answer = 0;
    for(auto iter=prefix_A.begin(); iter != prefix_A.end(); iter++) {
        map<long long, long long>::iterator next;
        if((next = prefix_B.find(T - iter->first)) != prefix_B.end()) {
            answer += iter->second * next->second;
        }
    }

    return answer;
}

int main() {

    cin >> T;
    cin >> N;
    
    A.resize(N);
    for(int i=0; i<N; i++) {
        cin >> a;   
        A[i] = a;
    }

    cin >> M;
    B.resize(M);
    for(int i=0; i<M; i++) {
        cin >> b;
        B[i] = b;
    }

    cout << solve();
}