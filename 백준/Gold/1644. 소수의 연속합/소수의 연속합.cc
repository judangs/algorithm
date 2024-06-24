#include <iostream>
#include <vector>

using namespace std;

int N;
vector<bool> prime;
vector<int> number;

int solve() {

    prime.resize(4000001, true);
    for(int i=2; i<=4000000; i++) {
        for(int j=i; j<=4000000; j+=i) {
            if(i != j) prime[j] = false;
        }
    }

    for(int i=2; i<prime.size(); i++) {
        if(prime[i] == true)
            number.push_back(i);
    }

    int answer = 0;
    for(int current=0; current<number.size(); current++) {
        if(number[current] > N) break;

        int sum = 0;
        for(int next=current; next<number.size(); next++) {
            sum += number[next];
            if(sum >= N) {
                if(sum == N) answer++;
                break;
            }
        }
    }

    return answer;

}

int main() {
    cin >> N;
    cout << solve();
}