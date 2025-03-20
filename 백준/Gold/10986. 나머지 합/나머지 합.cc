#include <iostream>
#include <vector>

using namespace std;

int N, M, A;
vector<long long> prefix;
vector<long long> group;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;

    group.resize(M, 0);
    prefix.push_back(0);

    long long answer = 0;
    for(int i=0; i<N; i++) {
        cin >> A;
        
        long long sum = (prefix.back() + A) % M;
        if(sum == 0)
            answer++;

        prefix.push_back(sum);
        group[sum]++;
    }

    for(int sum=0; sum<M; sum++) {
        if(group[sum] > 1) {
            answer += (group[sum] * (group[sum] - 1)) / 2;
        }
    }

    cout << answer;
}