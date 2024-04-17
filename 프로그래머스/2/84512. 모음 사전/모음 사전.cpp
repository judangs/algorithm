#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<char> dictionary = {'A', 'E', 'I', 'O', 'U'};
map<string, int> m;
int step = 1;

void dfs(int depth, string word, string current) {
    if(depth == 5) {
        return;
    }

    for(int i=0; i<dictionary.size(); i++) {
        m[current + dictionary[i]] = step++;
        dfs(depth + 1, word, current + dictionary[i]);
    }
}

int solution(string word) {
    dfs(0, word, "");
    return m[word];
}