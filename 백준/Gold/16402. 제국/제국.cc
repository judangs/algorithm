#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <map>

using namespace std;

int N, M;
string kingdom[501];
int parent[501];

map<string, int> name2idx;

string naming(string name) {
    stringstream iss(name);
    string buffer; vector<string> ret;
    
    while(getline(iss, buffer, ' ')) {
        ret.push_back(buffer);
    }

    return ret.back();
}

pair<int, int> war(string word) {
    stringstream iss(word);
    string buffer; vector<string> ret;
    
    while(getline(iss, buffer, ',')) {
        ret.push_back(buffer);
    }

    string front = naming(ret[0]), back = naming(ret[1]);
    if(stoi(ret[2]) == 1) return {name2idx[back], name2idx[front]};
    return {name2idx[front], name2idx[back]};
}

int find(int now) {
    if(parent[now] == now) return now;
    return (parent[now] = find(parent[now]));
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    cin.ignore();

    for(int i=0; i<N; i++) {
        string word; getline(cin, word);
        string name = naming(word);
        parent[i] = i; name2idx[name] = i;
        kingdom[i] = name;
    }

    for(int i=0; i<M; i++) {
        string word; getline(cin, word);
        auto [loser, winner] = war(word);
     
        if(find(loser) == find(winner)) {
            parent[winner] = winner;    
            parent[find(loser)] = find(winner);
        }
        else {
            parent[winner] = find(winner);
            parent[find(loser)] = find(winner);
        }
    }

    vector<string> answer;
    for(int i=0; i<N; i++) {
        if(parent[i] == i)
            answer.push_back("Kingdom of " + kingdom[i]);
    }

    sort(answer.begin(), answer.end());

    cout << answer.size() << endl;
    for(auto ans: answer) {
        cout << ans << endl;
    }
}