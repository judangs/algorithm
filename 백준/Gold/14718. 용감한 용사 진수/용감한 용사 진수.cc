#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


const int inf = 1e9;
int N, K;
vector<int> ability[3];
struct Node {
    int str, dex, inte;
};
vector<Node> solidier;

bool win(int str, int dex, int inte) {
    int count = 0;
    for(auto node: solidier) {
        if(node.str <= str && node.dex <= dex && node.inte <= inte)
            count++;
    }

    return (count >= K);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> K;
    for(int idx=0; idx<N; idx++) {
        int s, d, i; cin >> s >> d >> i;
        ability[0].push_back(s); 
        ability[1].push_back(d);
        ability[2].push_back(i);
        solidier.push_back({s, d, i});
    }

    for(int i=0; i<3; i++)
        sort(ability[i].begin(), ability[i].end());

    int answer = inf;
    for(auto str: ability[0]) {
        for(auto dex: ability[1]) {
            for(auto inte: ability[2]) {
                if(win(str, dex, inte)) {
                    answer = min(answer, (str + dex + inte));
                }
            }
        }
    }

    cout << answer << endl;
    
}