#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstdlib>

#define fastio ios::sync_with_stdio(false); cin.tie(NULL);

using namespace std;

int N;
int eday[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int psum[13] = { 0, };

struct Date;
int daytime(const Date & date);

struct Date {
    int month;
    int day;

    bool operator==(const Date & o) const {
        return daytime(*this) == daytime(o);
    }

    bool operator<(const Date & o) const {
        return daytime(*this) < daytime(o);
    }

    bool operator<=(const Date & o) const {
        return daytime(*this) <= daytime(o);
    }    
};
struct Period {
    Date start;
    Date end;
};
vector<Period> periods;

int daytime(const Date & date) {
    return psum[date.month] + date.day;
}

int main() {

    fastio;
    cin >> N;
    periods = vector<Period>(N);

    for(int i = 2; i <= 12; i++)
        psum[i] = psum[i - 1] + eday[i - 1];

    
    for(int i = 0; i < N; i++) {
        int sm, sd, em, ed; cin >> sm >> sd >> em >> ed;
        periods[i] = Period { Date{ sm, sd }, Date{ em, ed }};
    }

    sort(periods.begin(), periods.end(), [&](const Period & l, const Period & r) {
        if(daytime(l.start) == daytime(r.start)) {
            return daytime(l.end) < daytime(r.end);
        }
        return daytime(l.start) < daytime(r.start);
    });

    Date now = Date { 3, 1 };
    int idx = 0;
    int answer = 0;

    while(now <= Date { 11, 30 }) {

        Date end = now;
        while( idx < N && periods[idx].start <= now) {
            if(daytime(end) < daytime(periods[idx].end)) {
                end = periods[idx].end;
            }
            idx++;
        }

        if( end == now ) {
            cout << "0" << endl;
            exit(0);
        }

        now = end;
        answer++;
    }
    
    cout << answer << endl;

}