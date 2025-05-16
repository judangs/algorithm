#include <iostream>
#include <cstring>
#include <queue>
#include <algorithm>

#define INF 1e9

using namespace std;

int N;
string word;

struct compare {
    bool operator()(const string a, const string b) {
        return (a + b) > (b + a);
    }
};
priority_queue<string, vector<string>, compare> pq;


int main() {

    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> word;
        pq.push(word);
    }

    string answer = "";
    while(!pq.empty()) {
        auto w = pq.top();
        pq.pop();

        answer += w.front();
        if(w.size() > 1) 
            pq.push(w.substr(1));
        
    }


    cout << answer;
}