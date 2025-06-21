#include <iostream>
#include <vector>
#include <map>

#define INF 1e9

using namespace std;


static int dy[] = {-1, 0, 1, 0};
static int dx[] = {0, 1, 0, -1};

struct Position {
    int y, x;
};

int N, M;
vector<vector<char>> ground;

namespace object {

    struct ItemBox {
        string type;
        int ability;

        ItemBox() { }
        ItemBox(string _t): type(_t) { }
        ItemBox(char _t, int _a): type(string(1, _t)), ability(_a) { }
    };

    class Character {
        protected:
            int mhealth, health;
            int atk, def;

            Character(int _h, int _d, int _s): mhealth(_h), health(_h), atk(_d), def(_s) { }
            
        public:

            bool alive() { return (0 < health); }
            virtual int attack() { return atk; }
            virtual bool damage(int d) { 
                health -= max(1, d - def); 
                health = max(0, health);
                return alive(); 
            }
            void heal(int h) { health = min(mhealth, health + h); }
            
    };

    class Player : public Character {
        private:
            Position pos;
            int level, exp;
            int weapon, armor;

        public:
            map<string, bool> accessories;

            Player(int _y, int _x): Character(20, 2, 2), pos({_y, _x}) {
                level = 1, exp = 0;
                weapon = 0, armor = 0;
            }

            void status() {
                cout << "LV : " << level << "\n";
                cout << "HP : " << health << "/" << mhealth << "\n";
                cout << "ATT : " << atk << "+" << weapon << "\n";
                cout << "DEF : " << def << "+" << armor << "\n";
                cout << "EXP : " << exp << "/" << (5 * level) << "\n";
            }

            void go(Position next) {
                pos = next;
            }

            Position where() { return pos; }

            bool own(string accessary) {
                if(accessories.find(accessary) != accessories.end())
                    return true;
                return false;
            }

            void rewarding(int reward) {
                exp += reward;
                if(exp >= 5 * level) {
                    level++, exp = 0;
                    mhealth += 5, atk += 2, def += 2;
                    health = mhealth;
                    
                }
            }

            int attack() override { return (weapon + atk); }
            bool damage(int d) override { 
                health -= max(1, d - (def + armor)); 
                health = max(0, health);
                return alive(); }            

            void respawn(Position start) {
                this->pos = start;
                accessories.erase("RE");
                health = mhealth;
            }

            Position move(char dir) {
                int d;
                if(dir == 'L') d = 3; if(dir == 'U') d = 0;
                if(dir == 'R') d = 1; if(dir == 'D') d = 2;

                int ny = pos.y + dy[d], nx = pos.x + dx[d];
                if(0 < ny && ny <= N && 0 < nx && nx <= M) {
                    if(ground[ny][nx] != '#') 
                        return Position{ny, nx};
                }
                return Position{pos.y, pos.x};
            }

            bool trap(int v) { 
                health -= v; 
                health = max(0, health);
                return alive(); 
            }

            bool can_open_box(ItemBox itembox) {
                if(itembox.type == "W") {
                    weapon = itembox.ability;
                    return true;
                }
                if(itembox.type == "A") {
                    armor = itembox.ability;
                    return true;
                }
                
                if(accessories.size() < 4) {
                    if(accessories.find(itembox.type) == accessories.end()) {
                        accessories[itembox.type] = true;
                        return true;
                    }
                }

                return false;
            }
    };

    class Monster : public Character {
        
        private:
            string name;
            int reward;
            
        public:
            
            Monster(string _s, int _w, int _a, int _h, int _e): Character(_h, _w, _a) {
                name = _s;
                reward = _e;
            }

            int drop() { return reward; }
            string named() {return name; }

    };

    vector<vector<Monster *>> monster;
    vector<vector<ItemBox>> item;    
}

Position start;
string command;

using namespace object;


bool match(Player * player, Monster * enemy, bool boss) {

    if(boss && player->own("HU")) player->heal(INF);

    int turn = 0;
    for(; player->alive() && enemy->alive(); turn++) {
        bool result;
        if(turn % 2 == 0) {
            if(turn == 0 && player->own("CO")) {
                if(player->own("DX")) result = enemy->damage(3 * player->attack());
                else result = enemy->damage(2 * player->attack());
            }
            else result = enemy->damage(player->attack());

            if(!result) {
                if(player->own("HR")) player->heal(3);

                if(player->own("EX")) player->rewarding((int)(1.2 * enemy->drop()));
                else player->rewarding(enemy->drop());

                return true;
            }
        }
        if(turn % 2 == 1) {
            if(boss && turn == 1 && player->own("HU")) continue;
            result = player->damage(enemy->attack());
            if(!result) {
                if(player->own("RE")) {
                    enemy->heal(INF);
                    player->respawn(start);
                }
                return false;
            }
        }
    }

    return player->alive();
}

bool kill = false;
string killer;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    ground.resize(N + 1, vector<char>(M + 1));
    item.resize(N + 1, vector<ItemBox>(M + 1));
    monster.resize(N + 1, vector<Monster *>(M + 1));
    
    int enemy = 0, box = 0;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            cin >> ground[i][j];
            if(ground[i][j] == '@') start = {i, j};
            if(ground[i][j] == 'M' || ground[i][j] == '&') enemy++;
            if(ground[i][j] == 'B') box++;
        }
    }

    cin >> command;

    for(int i=0; i<enemy; i++) {
        string S; int R, C, W, A, H, E; cin >> R >> C >> S >> W >> A >> H >> E;

        Monster * alive = new Monster(S, W, A, H, E);
        monster[R][C] = alive;
    }

    for(int i=0; i<box; i++) {
        int R, C; char T; cin >> R >> C >> T;
        if(T == 'W' || T == 'A') {
            int S; cin >> S;
            item[R][C] = ItemBox{T, S};
        }
        if(T == 'O') {
            string S; cin >> S;
            item[R][C] = ItemBox{S};
        }
    }

    Player * player = new Player(start.y, start.x);
    
    int step = 0;
    for(auto & dir: command) {

        step++;
        if(!player->alive()) break;

        auto prev = player->where(), pos = player->move(dir);
        player->go(pos);

        if(ground[pos.y][pos.x] == '^') {
            if(player->own("DX")) player->trap(1);
            else player->trap(5);

            if(!player->alive()) {
                if(player->own("RE")) player->respawn(start);
                else {
                    killer = "SPIKE TRAP";
                    break;
                };
            }
        }
        if(ground[pos.y][pos.x] == 'B') {
            ItemBox itembox = item[pos.y][pos.x];
            bool open = player->can_open_box(itembox);
            ground[pos.y][pos.x] = '.';
        }
        if(ground[pos.y][pos.x] == '&') {

            Monster * m = monster[pos.y][pos.x];
            bool win = match(player, m, false);
            if(win) ground[pos.y][pos.x] = '.';
            else {
                if(player->alive()) continue;
                killer = m->named();
                break;
            }
            
        }
        if(ground[pos.y][pos.x] == 'M') {

            Monster * m = monster[pos.y][pos.x];
            bool win = match(player, m, true);
            if(win) {
                ground[pos.y][pos.x] = '.'; 
                kill = true;
                break;
            }
            else {
                if(player->alive()) continue;
                killer = m->named();
                break;
            }
        }
    }

    ground[start.y][start.x] = '.';
    if(player->alive())
        ground[player->where().y][player->where().x] = '@';

    for(int i=1; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            
            cout << ground[i][j];
        }
        cout << "\n";
    }

    cout << "Passed Turns : " << step << "\n";
    player->status();

    if(player->alive()) {
        if(kill) cout << "YOU WIN!";
        else cout << "Press any key to continue.";
    }
    else {
        cout << "YOU HAVE BEEN KILLED BY " <<  killer << "..";
    }
    

}