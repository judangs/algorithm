#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;

bool compare(vector<string> & person, vector<string> & team, int flow) {
    if(flow) {
        for(int i=0; i<N; i++)
            if(person[i] != team[i]) return false;
        return true;
    }
    else {
        for(int i=0; i<N; i++)
            if(person[i] != team[N - 1 - i]) return false;
        return true;
    }
}

int main() {

    cin >> N;
    vector<string> person(N);
    for(int i=0; i < N; i++) {
        cin >> person[i];
    }

    vector<string> team(person.begin(), person.end());
    sort(team.begin(), team.end());

    if(compare(person, team, 1)) cout << "INCREASING" << endl;
    else if(compare(person, team, 0)) cout << "DECREASING" << endl;
    else cout << "NEITHER" << endl;

}