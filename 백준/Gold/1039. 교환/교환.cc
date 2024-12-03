#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

string N;
int K;

struct Node {
    string cur;
    int count;
};

int main() {
    cin >> N >> K;

    int len = N.size();
    if (len < 2) {
        cout << -1 << endl;
        return 0;
    }

    queue<Node> q;
    set<pair<string, int>> visited;

    q.push({N, 0});
    visited.insert({N, 0});

    int answer = -1;

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        if (current.count == K) {
            answer = max(answer, stoi(current.cur));
            continue;
        }

        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                string next = current.cur;
                swap(next[i], next[j]);
                if (next[0] == '0') continue;

                if (visited.find({next, current.count + 1}) == visited.end()) {
                    q.push({next, current.count + 1});
                    visited.insert({next, current.count + 1});
                }
            }
        }
    }

    cout << answer << endl;
}
