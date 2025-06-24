#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
#include <cmath>

using namespace std;
typedef long long ll;

string expression;
vector<int> num[3];

const int INF = 1e9;

struct Node {
    vector<int> A, B, C;
    bool valid;

    Node() { valid = false; }
    Node(bool _v): valid(_v) { }    

    int compare(const vector<int> & l, const vector<int> & r) const {
        if(l.size() == r.size()) {
            for(int i=0; i<l.size(); i++)
                if(l[i] != r[i]) {
                    return (l[i] < r[i] ? 1 : -1);
                }
            
            return 0;
        }
        
        return (l.size() < r.size() ? 1: -1);
    }

    void add(int _a, int _b, int _c) {
        A.push_back(_a); B.push_back(_b); C.push_back(_c);
        valid = true;
    }

    void erase() {
        A.pop_back(); B.pop_back(); C.pop_back();
    }

    bool operator<(const Node & o) const {

        if(compare(C, o.C) == 0) 
            return (0 < compare(A, o.A));
        return (0 < compare(C, o.C));
    }
};

Node dp[2][55];
bool visited[2][55];
int nsz[3];

int mlen;


void insert(string number, int idx, int sz) {

    nsz[idx] = number.size();

    for(int i=number.size()-1; i >= 0; i--) {
        if(number[i] == '?') num[idx].push_back(-1);
        else num[idx].push_back(number[i] - '0');
    }

    while(num[idx].size() < sz) num[idx].push_back(0);
}

void parse() {

    int plus = expression.find('+'), equals = expression.find('=');

    string n1 = expression.substr(0, plus);
    string n2 = expression.substr(plus + 1, equals - plus - 1);
    string n3 = expression.substr(equals + 1);

    int sz = max({n1.size(), n2.size(), n3.size()}) + 1;

    insert(n1, 0, sz), insert(n2, 1, sz), insert(n3, 2, sz);
    mlen = max(nsz[0], nsz[1]);
}


Node interpret(int pos, int carry) {
    
    if(pos == mlen) {
        if(mlen + 1 == nsz[2]) {
            if(carry != 1) return Node{false};
            if(num[2][pos] != -1 && num[2][pos] != 1) return Node{false};
            return Node{true};
        }

        if(mlen == nsz[2]) {
            if(carry == 0) return Node{true};
        }

        return Node{false};
    }

    int bit = carry == 0 ? 0 : 1;
    if(visited[bit][pos]) return dp[bit][pos];

    vector<int> possible[3];
    int id = 0;
    for(auto & now: {num[0][pos], num[1][pos], num[2][pos]}) {
        if(now == -1) {
            for(int can=0; can<10; can++) possible[id].push_back(can);
        }
        else
            possible[id].push_back(now);

        id++;
    }

    auto & ret = dp[bit][pos];
    visited[bit][pos] = true;

    for(auto & front: possible[0]) {
        for(auto & back: possible[1]) {
            for(auto & ans: possible[2]) {

                if(pos == nsz[0] - 1 && 1 < nsz[0] && front == 0) continue;
                if(pos == nsz[1] - 1 && 1 < nsz[1] && back == 0) continue;
                if(pos == nsz[2] - 1 && 1 < nsz[2] && ans == 0) continue;


                int sum = front + back + carry;
                if(sum % 10 == ans) {
                    Node state = interpret(pos + 1, sum / 10);
                    if(state.valid) {
                        ll ten = 1ll;
                        for(int i=0; i<pos; i++) ten *= 10;

                        state.add(front, back, ans);
                        if(!ret.valid || ret < state) ret = state;
                        state.erase();
                    }
                }
            }
        }
    }

    return ret;
}

void print(vector<int> su, int idx) {
    bool zero = true;
    for(int i=0; i<su.size(); i++) {
        if(zero && su[i] == 0) continue;
        cout << su[i];
        zero = false;
    }

    if(zero) cout << "0";
}

int main() {

    memset(visited, false, sizeof(visited));
    cin >> expression;
    
    parse();

    Node answer = interpret(0, 0); 

    if(!answer.valid) cout << "-1";
    else {
        if(mlen == nsz[2]) {
            print(answer.A, 0); cout << "+"; print(answer.B, 1); cout << "="; print(answer.C, 2);
        }
        else {
            answer.C.insert(answer.C.begin(), 1);
            print(answer.A, 0); cout << "+"; print(answer.B, 1); cout << "="; print(answer.C, 2);
        }
    }

}