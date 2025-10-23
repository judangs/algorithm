#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define fastio ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

using namespace std;

int T, N;

struct Player {
    int location;
    map<int, int> items;

    Player() : location(1) {}
};
vector<Player> players;

int main() {

    fastio;
    cin >> T >> N;
    players.resize(N + 1);

    vector<int> illegal, cheat;
    while(T--) {
        int num, idx; char op;
        cin >> num >> idx >> op;

        if(op == 'M') {
            int next; cin >> next;
            players[idx].location = next;
        }
        if(op == 'F') {
            int item; cin >> item;
            if(item != players[idx].location) {
                illegal.push_back(num);
            }
            players[idx].items[item]++;
        }
        if(op =='A') {
            int enemy; cin >> enemy;
            if(players[idx].location != players[enemy].location) {
                illegal.push_back(num);
                cheat.push_back(idx);
            }
        }
        if(op == 'C') {
            int l, r; cin >> l >> r;
            bool found = false;
            if(players[idx].items.find(l) == players[idx].items.end()) {
                if(!found) {
                    illegal.push_back(num);
                    found = true;
                }
            }
            else {
                players[idx].items[l]--;
                if(players[idx].items[l] == 0) {
                    players[idx].items.erase(l);
                }
            }
            
            if(players[idx].items.find(r) == players[idx].items.end()) {
                if(!found) {
                    illegal.push_back(num);
                    found = true;
                }
            }
            else {
                players[idx].items[r]--;
                if(players[idx].items[r] == 0) {
                    players[idx].items.erase(r);
                }
            }
        }
    }
    
    sort(illegal.begin(), illegal.end());
    sort(cheat.begin(), cheat.end());
    cheat.erase(unique(cheat.begin(), cheat.end()), cheat.end());
    cout << illegal.size() << "\n"; 
    for(auto & log: illegal) {
        cout << log << " ";
    }
    if(illegal.size() != 0) cout << endl;
    cout << cheat.size() << "\n";
    for(auto & log: cheat) {
        cout << log << " ";
    }

}