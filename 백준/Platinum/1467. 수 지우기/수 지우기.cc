#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

string n, e;

int usage[10] = {0, };
int erase[10] = {0, };
vector<int> visited(10, 0);

int main() {
    cin >> n >> e;

    for(auto & c: n) usage[c - '0']++;
    for(auto & c: e) {
        usage[c - '0']--;
        erase[c - '0']++;
    }

    int len = (n.size() - e.size());
    int size = -1;
    
    string answer = "";
    while(len--) {
        for(int num=9; num >= 0; num--) {

            bool usable = true;
            if(usage[num] > 0) {

                fill(visited.begin(), visited.end(), 0);

                for(int p=size + 1; p < n.size() && n[p] != ('0' + num); p++) {
                    visited[n[p] - '0']++;
                }

                for(int next=0; next <= 9; next++) {
                    if(visited[next] > erase[next]) {
                        usable = false;
                    }
                }

                if(usable) {

                    for(int p=size + 1; n[p] != ('0' + num); p++) {
                        erase[n[p] - '0']--;
                        size++;
                    }

                    answer += to_string(num);
                    usage[num]--;
                    size++;
                    break;
                } 
            }

        }
    }

    cout << answer << "\n";
}