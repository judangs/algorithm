#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

typedef vector<int> vi;

struct Node {
    int idx;
    int position;
    Node * left;
    Node * right;

    Node(int p, int pos, Node * l, Node * r): idx(p), position(pos), left(l), right(r) {};
};

bool compare(pair<int, vi> a, pair<int, vi> b) {
    return a.second.back() > b.second.back();
}

vector<pair<int, vi>> node_list;
vector<int> pre_order_list;
vector<int> post_order_list;

void find(Node * current, Node * next) {
    if(current->left == NULL && current->position > next->position) {
        current->left = next;
        return;
    }
    if(current->right == NULL && current->position < next->position) {
        current->right = next;
        return;
    }
    if(current->position > next->position) find(current->left, next);
    if(current->position < next->position) find(current->right, next);
}

void pre_order(Node * current) {
    pre_order_list.push_back(current->idx);
    if(current->left != NULL) pre_order(current->left);
    if(current->right != NULL) pre_order(current->right);
}

void post_order(Node * current) {
    if(current->left != NULL) post_order(current->left);
    if(current->right != NULL) post_order(current->right);
    post_order_list.push_back(current->idx);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
        
    for(int idx=0; idx<nodeinfo.size(); idx++) {
        node_list.push_back({idx + 1, nodeinfo[idx]});
    }

    sort(node_list.begin(), node_list.end(), compare);
    
    Node * root = new Node(node_list.front().first, node_list.front().second.front(), NULL, NULL);
    for(int idx=1; idx<node_list.size(); idx++) {
        Node * next = new Node(node_list[idx].first, node_list[idx].second.front(), NULL, NULL);
        find(root, next);
    }

    pre_order(root);
    post_order(root);

    return {pre_order_list, post_order_list};
}