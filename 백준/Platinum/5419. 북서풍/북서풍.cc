#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#define MAXSZ 75001

using namespace std;

struct SegTree {
    vector<int> arr;
    
    SegTree() : arr(4 * MAXSZ, 0) {}
    
    void update(int node, int l, int r, int pos) {
        if (pos < l || pos > r) return;
        if (l == r) {
            arr[node]++;
            return;
        }
        
        int m = (l + r) / 2;
        update(2 * node, l, m, pos);
        update(2 * node + 1, m + 1, r, pos);
        arr[node] = arr[2 * node] + arr[2 * node + 1];
    }
    
    int query(int node, int l, int r, int s, int e) {
        if (r < s || e < l) return 0;
        if (s <= l && r <= e) return arr[node];
        
        int m = (l + r) / 2;
        return query(2 * node, l, m, s, e) + query(2 * node + 1, m + 1, r, s, e);
    }
};

struct Island {
    int x, y;
    
    bool operator<(const Island& other) const {
        if (y == other.y) return x < other.x;
        return y > other.y;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        cin >> N;
        
        vector<Island> islands(N);
        vector<int> x_coords;
        
        for (int i = 0; i < N; i++) {
            cin >> islands[i].x >> islands[i].y;
            x_coords.push_back(islands[i].x);
        }
        
        sort(x_coords.begin(), x_coords.end());
        x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());
        
        sort(islands.begin(), islands.end());
        
        SegTree seg;
        long long answer = 0;
        
        for (int i = 0; i < N; i++) {
            int compressed_x = lower_bound(x_coords.begin(), x_coords.end(), islands[i].x) - x_coords.begin();
            
            answer += seg.query(1, 0, x_coords.size() - 1, 0, compressed_x);
            seg.update(1, 0, x_coords.size() - 1, compressed_x);
        }
        
        cout << answer << "\n";
    }
    
}