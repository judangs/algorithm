#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace std;

int N, M;
int A, B, C;

vector<int> arr;
vector<tuple<int, int, int>> edges;


bool compare(tuple<int, int, int> a, tuple<int, int, int> b) {
    return get<2>(a) < get<2>(b);
}

int find(int start) {
    if(arr[start] == start)
        return start;
    return find(arr[start]);
}

int solve() {

    int group = N;
    arr.resize(N + 1);
    for(int i=1; i<=N; i++) arr[i] = i;

    int answer = 0;

    for(auto edge: edges) {
        if(group == 2) break;

        int start, end, cost;
        tie(start, end, cost) = edge;

        start = find(start);
        end = find(end);
        if(start != end) {

            answer += cost;
            group -= 1;

            if(start < end)
                arr[end] = start;
            else
                arr[start] = end;
        }
    }

    return answer;
}

int main() {
    cin >> N >> M;

    edges.resize(M);
    for(int i=0; i<M; i++) {
        cin >> A >> B >> C;
        edges.push_back(make_tuple(A, B, C));
    }

    sort(edges.begin(), edges.end(), compare);
    cout << solve();
}