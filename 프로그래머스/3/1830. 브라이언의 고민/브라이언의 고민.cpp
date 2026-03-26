#include <string>
#include <vector>
#include <cctype>

using namespace std;

bool parseRule1(const string& s, int l, int r, int c, string& out) {
    if ((r - l + 1) < 3) return false;
    if ((r - l + 1) % 2 == 0) return false;

    out.clear();
    for (int i = l; i <= r; i++) {
        if ((i - l) % 2 == 0) {
            if (!isupper((unsigned char)s[i])) return false;
            out += s[i];
        } else {
            if (s[i] != char('a' + c)) return false;
        }
    }
    return true;
}

bool parseRule2(const string& s, int start, int c,
                const vector<vector<int>>& pos,
                const vector<int>& kind,
                vector<bool>& used,
                int& nextPos,
                string& out) {
    if (used[c]) return false;
    if (kind[c] != 2) return false;
    if (pos[c].size() != 2) return false;
    if (pos[c][0] != start) return false;

    int end = pos[c][1];
    if (end <= start + 1) return false;

    bool hasLower = false;
    for (int i = start + 1; i <= end - 1; i++) {
        if (islower((unsigned char)s[i])) {
            hasLower = true;
            break;
        }
    }

    out.clear();

    if (!hasLower) {
        for (int i = start + 1; i <= end - 1; i++) {
            if (!isupper((unsigned char)s[i])) return false;
            out += s[i];
        }
    } else {
        int inner = -1;
        for (int i = start + 1; i <= end - 1; i++) {
            if (islower((unsigned char)s[i])) {
                inner = s[i] - 'a';
                break;
            }
        }

        if (inner == -1) return false;
        if (used[inner]) return false;
        if (kind[inner] != 1) return false;

        for (int i = start + 1; i <= end - 1; i++) {
            if (islower((unsigned char)s[i]) && s[i] != char('a' + inner)) {
                return false;
            }
        }

        if (!parseRule1(s, start + 1, end - 1, inner, out)) return false;
        used[inner] = true;
    }

    used[c] = true;
    nextPos = end + 1;
    return true;
}

string solution(string sentence) {
    int n = sentence.size();

    vector<vector<int>> pos(26);
    for (int i = 0; i < n; i++) {
        if ('a' <= sentence[i] && sentence[i] <= 'z') {
            pos[sentence[i] - 'a'].push_back(i);
        }
    }

    vector<int> kind(26, 0);
    for (int c = 0; c < 26; c++) {
        int cnt = pos[c].size();
        if (cnt == 0) continue;

        if (cnt != 2) {
            kind[c] = 1;
        } else {
            int gap = pos[c][1] - pos[c][0] - 1;
            if (gap >= 2) kind[c] = 2;
            else kind[c] = 3;
        }
    }

    for (int c = 0; c < 26; c++) {
        if (kind[c] != 3) continue;

        bool insideOtherRule2 = false;
        for (int d = 0; d < 26; d++) {
            if (c == d) continue;
            if (kind[d] != 2) continue;
            if (pos[d][0] < pos[c][0] && pos[c][1] < pos[d][1]) {
                insideOtherRule2 = true;
                break;
            }
        }
        kind[c] = insideOtherRule2 ? 1 : 2;
    }

    vector<bool> used(26, false);
    string answer = "";

    for (int i = 0; i < n; ) {
        if (islower((unsigned char)sentence[i])) {
            int c = sentence[i] - 'a';
            string word;
            int nextPos;

            if (!parseRule2(sentence, i, c, pos, kind, used, nextPos, word)) {
                return "invalid";
            }

            if (!answer.empty()) answer += ' ';
            answer += word;
            i = nextPos;
        } else {
            if (!isupper((unsigned char)sentence[i])) return "invalid";

            if (i + 1 < n && islower((unsigned char)sentence[i + 1])) {
                int c = sentence[i + 1] - 'a';

                if (kind[c] == 1 && !used[c] && !pos[c].empty() && pos[c][0] == i + 1) {
                    int r = pos[c].back() + 1;
                    string word;

                    if (r >= n) return "invalid";
                    if (!parseRule1(sentence, i, r, c, word)) return "invalid";

                    used[c] = true;
                    if (!answer.empty()) answer += ' ';
                    answer += word;
                    i = r + 1;
                    continue;
                }
            }

            int j = i;
            while (j < n && isupper((unsigned char)sentence[j])) {
                if (j + 1 < n && islower((unsigned char)sentence[j + 1])) {
                    int c = sentence[j + 1] - 'a';
                    if (kind[c] == 1 && !used[c] && !pos[c].empty() && pos[c][0] == j + 1) {
                        break;
                    }
                }
                j++;
            }

            if (j == i) return "invalid";

            if (!answer.empty()) answer += ' ';
            answer += sentence.substr(i, j - i);
            i = j;
        }
    }

    for (int c = 0; c < 26; c++) {
        if (!pos[c].empty() && !used[c]) return "invalid";
    }

    return answer;
}