#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<int> person;
map<string, bool> visit;

vector<int> solution(int n, vector<string> words) {
    person.resize(n, 0);

    char next = words.front().front();
    int turn = 0;
    for(string word: words) {
        if(visit[word] == false && word.front() == next) {
            visit[word] = true;
            person[turn++ % n]++;
            next = word.back();
        }
        else {
            return vector<int>{(turn % n) + 1, person[turn % n] + 1};
        }
    }

    return vector<int>{0, 0};
}