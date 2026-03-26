#include <string>
#include <vector>
#include <algorithm>

using namespace std;

extern string submit(int);

struct Result {
    int strike;
    int ball;
};

vector<int> all_candidates;

// guess를 질문했을 때 secret에 대한 결과 계산
Result get_result(int guess, int secret) {
    string g = to_string(guess);
    string s = to_string(secret);

    int strike = 0;
    int ball = 0;

    for (int i = 0; i < 4; i++) {
        if (g[i] == s[i]) strike++;
    }

    for (int i = 0; i < 4; i++) {
        if (g[i] == s[i]) continue;
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;
            if (g[i] == s[j]) {
                ball++;
                break;
            }
        }
    }

    return {strike, ball};
}

// "xS yB" 파싱
Result parse_response(const string& r) {
    return {r[0] - '0', r[3] - '0'};
}

// 현재 alive 후보들을 가장 잘 분할하는 질문 선택
int pick_best_guess(const vector<int>& alive) {
    int best_guess = -1;
    int best_worst = 1e9;
    bool best_in_alive = false;

    for (int guess : all_candidates) {
        int bucket[5][5] = {0};

        for (int secret : alive) {
            Result res = get_result(guess, secret);
            bucket[res.strike][res.ball]++;
        }

        int worst = 0;
        for (int s = 0; s <= 4; s++) {
            for (int b = 0; b <= 4; b++) {
                worst = max(worst, bucket[s][b]);
            }
        }

        bool in_alive = binary_search(alive.begin(), alive.end(), guess);

        if (worst < best_worst) {
            best_worst = worst;
            best_guess = guess;
            best_in_alive = in_alive;
        } else if (worst == best_worst) {
            // 동점이면 살아있는 후보를 우선
            if (in_alive && !best_in_alive) {
                best_guess = guess;
                best_in_alive = true;
            } else if (in_alive == best_in_alive && guess < best_guess) {
                best_guess = guess;
            }
        }
    }

    return best_guess;
}

// 가능한 모든 4자리 후보 생성 (1~9, 중복 없음)
void generate_candidates() {
    vector<int> digits = {1,2,3,4,5,6,7,8,9};

    for (int a = 0; a < 9; a++) {
        for (int b = 0; b < 9; b++) {
            if (b == a) continue;
            for (int c = 0; c < 9; c++) {
                if (c == a || c == b) continue;
                for (int d = 0; d < 9; d++) {
                    if (d == a || d == b || d == c) continue;
                    int num = digits[a] * 1000 + digits[b] * 100 + digits[c] * 10 + digits[d];
                    all_candidates.push_back(num);
                }
            }
        }
    }

    sort(all_candidates.begin(), all_candidates.end());
}

int solution(int n) {
    generate_candidates();

    vector<int> alive = all_candidates;

    while (n-- > 0 && !alive.empty()) {
        int guess = pick_best_guess(alive);
        string response = submit(guess);
        Result target = parse_response(response);

        if (target.strike == 4 && target.ball == 0) {
            return guess;
        }

        vector<int> next_alive;
        next_alive.reserve(alive.size());

        for (int secret : alive) {
            Result cur = get_result(guess, secret);
            if (cur.strike == target.strike && cur.ball == target.ball) {
                next_alive.push_back(secret);
            }
        }

        alive.swap(next_alive);

        if (alive.size() == 1) {
            return alive[0];
        }
    }

    return alive.empty() ? -1 : alive[0];
}