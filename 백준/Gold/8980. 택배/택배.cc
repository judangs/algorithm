#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, C, M;
struct Package {
    int start, end, count;

    bool operator<(const Package & o) const {
        if(end == o.end)
            return start < o.start;
        return end < o.end;
    }
};

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> C;
    cin >> M;

    vector<int> capacity(N + 1, C);
    vector<Package> packages;
    while(M--) {
        int a, b, c; cin >> a >> b >> c;
        packages.push_back({a, b, c});
    }

    sort(packages.begin(), packages.end());


    int answer = 0;
    for(auto & [start, end, count]: packages) {
        int cost = *min_element(capacity.begin() + start, capacity.begin() + end);
        int carry = min(cost, count);

        for(int villeage=start; villeage<end; villeage++)
            capacity[villeage] -= carry;

        answer += carry;
    }

    cout << answer << endl;

}