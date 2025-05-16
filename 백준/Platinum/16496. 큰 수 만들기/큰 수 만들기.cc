#include <iostream>
#include <queue>

using namespace std;

int A, N;

struct compare {
    bool operator()(string a, string b) {
        return (a + b) < (b + a);
    }
};

priority_queue<string, vector<string>, compare> pq;

int main() {

    cin >> N;
    for(int idx=0; idx<N; idx++) {
        cin >> A;
        pq.push(to_string(A));
    }

    string answer = "";
    while(!pq.empty()) {
        answer += pq.top();
        pq.pop();
    }

    bool zero = true;
    for(int idx=0; idx<answer.size(); idx++) {
        if(zero && answer[idx] == '0') continue;
        cout << answer[idx];
        zero = false;
    }

    if(zero) cout << "0";
}