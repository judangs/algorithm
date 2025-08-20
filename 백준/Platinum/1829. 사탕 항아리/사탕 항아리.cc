#include <iostream>
#include <vector>

using namespace std;

int N, K;

struct Info {
    int count;
    vector<int> selected;
};
vector<Info> answer;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K;

    if(K > N) {
        vector<int> select;
        for(int i=0; i<N; i++)
            select.push_back(i + 1);
        answer.push_back({K, select});

        K = 0;
    }

    vector<int> candy(N);
    for(int i=0; i<N; i++) candy[i] = K + i;

    for(int sz=N + K - 1, box=(sz + 1) / 2; 1 <= sz; sz -= box, box = (sz + 1) / 2) {
        vector<int> select;
        for(int i=0; i<N; i++) {
            if(box <= candy[i]) {
                candy[i] -= box;
                select.push_back(i + 1);
            }
        }

        if(!select.empty())
            answer.push_back({box, select});
    }

    cout << answer.size() << endl;
    for(auto & [count, select]: answer) {
        cout << select.size() << " " << count << endl;
        for(auto selected: select)
            cout << selected << " ";
        cout << endl;
    }

}