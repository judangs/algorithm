#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

#define MAXVERTEX 25000
#define INF 1e9

#define IN(x) (2 * (x))
#define OUT(x) (2 *(x) + 1)

using namespace std;

int N, M;
int source, sink;
pair<int, int> s, t;
vector<vector<char>> board;

struct Edge {
    int to;
    int capacity;
    int flow;
    Edge * reverse;

    Edge(int _to, int _capacity): to(_to), capacity(_capacity), flow(0) { }

    int residual() {
        return (capacity - flow);
    }   

    void push(int amount) {
        flow += amount;
        reverse->flow -= amount;
    } 
};

vector<vector<Edge *>> adj;

static int dy[] = {0, 1, 0, -1};
static int dx[] = {1, 0, -1, 0};

void divide_vertex(int in, int out) {
    Edge * forward = new Edge(out, 1), * backward = new Edge(in, 0);
    forward->reverse = backward, backward->reverse = forward;
    adj[in].push_back(forward);
    adj[out].push_back(backward);
}

void build_flow(int out, int in) {
    Edge * forward = new Edge(in, INF), * backward = new Edge(out, 0);
    forward->reverse = backward, backward->reverse = forward;
    adj[out].push_back(forward);
    adj[in].push_back(backward);
}

bool is_range(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < M;
}


int network_flow() {

    int answer = 0;

    while(true) {
        queue<int> q;
        vector<int> parent(MAXVERTEX, -1);
        vector<Edge *> child(MAXVERTEX);

        parent[source] = source;
        q.push(source);

        while(!q.empty() && parent[sink] == -1) {
            auto current = q.front(); q.pop();
            
            for(auto next: adj[current]) {
                if(next->residual() > 0 && parent[next->to] == -1) {
                    parent[next->to] = current;
                    child[next->to] = next;
                    q.push(next->to);
                }
            }
        }

        if(parent[sink] == -1) break;
        
        for(int node=sink; node!=source; node=parent[node]) {
            child[node]->push(1);
        }

        answer++;
    }

    return answer;
}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    board.resize(N, vector<char>(M));
    adj.resize(MAXVERTEX);

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> board[i][j];
            if(board[i][j] == 'K') s = {i, j};
            if(board[i][j] == 'H') t = {i, j};
        }
    }

    if(abs(s.first - t.first) + abs(s.second - t.second) == 1) {
        cout << "-1";
        return 0;
    }
    
    source = OUT(100 * s.first + s.second);
    sink = IN(100 * t.first + t.second);

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(board[i][j] == '#') continue;
            int in_from = IN(100 * i + j), out_from = OUT(100 * i + j);
            divide_vertex(in_from, out_from);

            for(int dir=0; dir<4; dir++) {
                int ny = i + dy[dir], nx = j + dx[dir];
                if(!is_range(ny ,nx)) continue;

                int in_to = IN(100 * ny + nx);
                build_flow(out_from, in_to);
            }
        }
    }

    cout << network_flow();

}