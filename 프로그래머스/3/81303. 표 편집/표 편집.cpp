#include <string>
#include <vector>
#include <stack>

using namespace std;

struct Node {
    int pos;
    Node * prev;
    Node * next;

    Node(int c, Node * p, Node * n): pos(c), prev(p), next(n) {};
};

stack<pair<Node *, Node *>> recover;


string solution(int n, int k, vector<string> cmd) {
    
    // front node equals NULL
    Node * prev = new Node(0, NULL, NULL);
    Node * current = prev;
    
    for(int i=1; i<=n; i++) {
        prev->next = new Node(i, prev, NULL);
        prev = prev->next;
    }

    // back node equals NULL;
    prev->next = new Node(0, prev, NULL);

    for(int i=0; i<k+1; i++) {
        current = current->next;        
    }

    for(auto & cmdline: cmd) {
        string command = cmdline.substr(0, 1);
        if(command == "U") {
            for(int i=0; i<stoi(cmdline.substr(2)); i++) {
                current = current->prev;
            }
        }
        else if(command == "D") {
            for(int i=0; i<stoi(cmdline.substr(2)); i++) {
                current = current->next;
            }
        }
        else if(command == "C") {
            recover.push(make_pair(current->prev, current));
            current->prev->next = current->next;
            current->next->prev = current->prev;

            if(current->next->pos == 0) {
                current = current->prev;
            }
            else {
                current = current->next;
            }
        }
        else {
            Node * recover_prev = recover.top().first;
            Node * recover_node = recover.top().second;

            recover.pop();

            recover_prev->next->prev = recover_node;
            recover_node->next = recover_prev->next;

            recover_prev->next = recover_node;
            recover_node->prev = recover_prev;
        }
    }

    string answer = string(n, 'O');
    while(!recover.empty()) {
        int idx = recover.top().second->pos;
        answer[idx-1] = 'X';

        recover.pop();
    }

    return answer;
}