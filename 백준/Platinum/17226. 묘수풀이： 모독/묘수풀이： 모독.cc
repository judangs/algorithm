#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cstring>

using namespace std;

int N, M;
bool solved = false;
vector<string> answer;

struct Card {
    int atk, hp;
};
vector<Card> player, opposite;

struct Node {
    int idx;
    int type;
    int hp;

    bool operator>(const Node & o) const {
        return hp > o.hp;
    }
};

bool spel() {
    vector<int> my_hp(N), enemy_hp(M);
    for(int i = 0; i < N; i++) {
        my_hp[i] = player[i].hp;
    }
    for(int i = 0; i < M; i++) {
        enemy_hp[i] = opposite[i].hp;
    }
    
    while(true) {
        bool someone_died = false;
        
        for(int i = 0; i < N; i++) {
            if(my_hp[i] > 0) {
                my_hp[i]--;
                if(my_hp[i] <= 0) {
                    someone_died = true;
                }
            }
        }
        
        for(int i = 0; i < M; i++) {
            if(enemy_hp[i] > 0) {
                enemy_hp[i]--;
                if(enemy_hp[i] <= 0) {
                    someone_died = true;
                }
            }
        }
        
        if(!someone_died) break;
    }
    
    for(int i = 0; i < M; i++) {
        if(enemy_hp[i] > 0) return false;
    }
    
    return true;
}
void play(int count, vector<bool> visit, vector<string> & command) {

    if(solved) return;
    if(count > N) return;

    command.push_back("use modok");
    if(spel()) {
        solved = true; answer = vector<string>(command.begin(), command.end());
        return;
    }
    command.pop_back();

    for(int i = 0; i < N; i++) {
        if(visit[i]) continue;
        for(int j = 0; j < M; j++) {
            if(opposite[j].hp <= 0) continue;

            visit[i] = true;
            Card p = player[i], q = opposite[j];
            player[i].hp -= q.atk, opposite[j].hp -= p.atk;
            command.push_back("attack " + to_string(i + 1) + " " + to_string(j + 1));
            play(count + 1, visit, command);
            command.pop_back();
            player[i].hp += q.atk, opposite[j].hp += p.atk;
            visit[i] = false;
        }

    }

}

int main() {

    cin >> N >> M;

    player = vector<Card> (N); opposite = vector<Card> (M);
    for(int i = 0; i < N; i++) {
        int atk, hp; cin >> atk >> hp;
        player[i] = { atk, hp };
    }

    for(int i = 0; i < M; i++) {
        int atk, hp; cin >> atk >> hp;
        opposite[i] = { atk, hp };
    }    

    if(M == 0) {
        cout << "0\n";
        return 0;
    }

    vector<bool> visit(N, false);
    vector<string> command;
    play(0, visit, command);

    if(solved) {
        cout << answer.size() << '\n';
        for(auto ans: answer) cout << ans << '\n';
    }
    else
        cout << "-1\n";
    


}