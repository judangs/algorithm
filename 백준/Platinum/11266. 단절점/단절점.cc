#include <iostream>
#include <vector>

using namespace std;

int id = 0;
int V, E;
vector<int> adj[100001];
int order[100001];
bool point[100001];


int ordering(int now, int parent) {

    order[now] = ++id; 
    int top = order[now], count = 0;

    for(auto child: adj[now]) {
        if(child == parent) continue;
        if(!order[child]) {

            count++;
            int super = ordering(child, now);

            if(parent != 0 && order[now] <= super) 
                point[now] = true;

            top = min(top, super);
        }
        else {
            top = min(top, order[child]);
        }
    }


    if(parent == 0 && 1 < count) point[now] = true;
    return top;

}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> V >> E;
    for(int i=0; i<E; i++) {
        int A, B; cin >> A >> B;
        adj[A].push_back(B), adj[B].push_back(A);
    }

    for(int vertex=1; vertex<=V; vertex++)
        if(!order[vertex])
            ordering(vertex, 0);

    vector<int> answer;
    for(int vertex=1; vertex<=V; vertex++)
        if(point[vertex])
            answer.push_back(vertex);

    cout << answer.size() << endl;
    for(auto ans: answer)
        cout << ans << " ";

}