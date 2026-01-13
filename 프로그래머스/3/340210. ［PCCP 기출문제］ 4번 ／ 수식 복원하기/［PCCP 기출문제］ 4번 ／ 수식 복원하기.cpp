#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

struct Exp {
    int l;
    int r;
    char op;
    int ans;
};

Exp parse(const string& expression) {
    stringstream ss(expression);
    string A, B, eq, C;
    char op;
    ss >> A >> op >> B >> eq >> C;

    int l = stoi(A);
    int r = stoi(B);
    int ans = (C == "X" ? -1 : stoi(C));
    return {l, r, op, ans};
}

int convert(int p, int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;

    int ret = 0, q = 1;
    while (n) {
        int d = n % 10;
        if (d >= p) return -1;
        ret += d * q;
        q *= p;
        n /= 10;
    }
    return ret;
}

bool check(int p, const Exp& e) {
    int L = convert(p, e.l);
    int R = convert(p, e.r);
    int A = convert(p, e.ans);
    if (L == -1 || R == -1 || A == -1) return false;

    if (e.op == '+') return (L + R == A);
    return (L - R == A);
}

string to_orig_str(int p, int n) {
    if (n == 0) return "0";
    string ret;
    while (n > 0) {
        ret.push_back(char('0' + (n % p)));
        n /= p;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

vector<string> solution(vector<string> expressions) {
    vector<Exp> exps;
    exps.reserve(expressions.size());
    for (auto &expression : expressions) exps.push_back(parse(expression));

    vector<bool> possible(10, true);

    for (int p = 2; p < 10; p++) {
        for (auto &e : exps) {
            if (convert(p, e.l) == -1 || convert(p, e.r) == -1) {
                possible[p] = false;
                break;
            }

            if (e.ans != -1) {
                if (!check(p, e)) {
                    possible[p] = false;
                    break;
                }
            }
        }
    }

    vector<string> answer;

    for (auto &e : exps) {
        if (e.ans != -1) continue;

        set<string> used;

        for (int p = 2; p < 10; p++) {
            if (!possible[p]) continue;

            int L = convert(p, e.l);
            int R = convert(p, e.r);
            if (L == -1 || R == -1) continue;

            int decRes = (e.op == '+') ? (L + R) : (L - R);

            if (decRes < 0) used.insert("X");
            else used.insert(to_orig_str(p, decRes));
        }

        string out = (used.size() == 1 ? *used.begin() : "?");
        answer.push_back(to_string(e.l) + " " + string(1, e.op) + " " +
                         to_string(e.r) + " = " + out);
    }

    return answer;
}
