#include <iostream>
#include <algorithm>
using namespace std;

int n;
int b[21][21];
int ans = 0;

int getmax(int a[21][21]) {
    int mx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mx = max(mx, a[i][j]);
        }
    }
    return mx;
}

void copy(int src[21][21], int dest[21][21]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

bool same(int a[21][21], int b[21][21]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] != b[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void up(int a[21][21]) {
    for (int j = 0; j < n; j++) {
        int t[21] = {0};
        int idx = 0;
        
        for (int i = 0; i < n; i++) {
            if (a[i][j] != 0) {
                t[idx++] = a[i][j];
            }
        }
        
        for (int i = 0; i < idx - 1; i++) {
            if (t[i] == t[i + 1]) {
                t[i] *= 2;
                t[i + 1] = 0;
                i++;
            }
        }
        
        int nt[21] = {0};
        idx = 0;
        for (int i = 0; i < n; i++) {
            if (t[i] != 0) {
                nt[idx++] = t[i];
            }
        }
        
        for (int i = 0; i < n; i++) {
            a[i][j] = nt[i];
        }
    }
}

void down(int a[21][21]) {
    for (int j = 0; j < n; j++) {
        int t[21] = {0};
        int idx = 0;
        
        for (int i = n - 1; i >= 0; i--) {
            if (a[i][j] != 0) {
                t[idx++] = a[i][j];
            }
        }
        
        for (int i = 0; i < idx - 1; i++) {
            if (t[i] == t[i + 1]) {
                t[i] *= 2;
                t[i + 1] = 0;
                i++;
            }
        }
        
        int nt[21] = {0};
        idx = 0;
        for (int i = 0; i < n; i++) {
            if (t[i] != 0) {
                nt[idx++] = t[i];
            }
        }
        
        for (int i = 0; i < n; i++) {
            a[n - 1 - i][j] = nt[i];
        }
    }
}

void left(int a[21][21]) {
    for (int i = 0; i < n; i++) {
        int t[21] = {0};
        int idx = 0;
        
        for (int j = 0; j < n; j++) {
            if (a[i][j] != 0) {
                t[idx++] = a[i][j];
            }
        }
        
        for (int j = 0; j < idx - 1; j++) {
            if (t[j] == t[j + 1]) {
                t[j] *= 2;
                t[j + 1] = 0;
                j++;
            }
        }
        
        int nt[21] = {0};
        idx = 0;
        for (int j = 0; j < n; j++) {
            if (t[j] != 0) {
                nt[idx++] = t[j];
            }
        }
        
        for (int j = 0; j < n; j++) {
            a[i][j] = nt[j];
        }
    }
}

void right(int a[21][21]) {
    for (int i = 0; i < n; i++) {
        int t[21] = {0};
        int idx = 0;
        
        for (int j = n - 1; j >= 0; j--) {
            if (a[i][j] != 0) {
                t[idx++] = a[i][j];
            }
        }
        
        for (int j = 0; j < idx - 1; j++) {
            if (t[j] == t[j + 1]) {
                t[j] *= 2;
                t[j + 1] = 0;
                j++;
            }
        }
        
        int nt[21] = {0};
        idx = 0;
        for (int j = 0; j < n; j++) {
            if (t[j] != 0) {
                nt[idx++] = t[j];
            }
        }
        
        for (int j = 0; j < n; j++) {
            a[i][n - 1 - j] = nt[j];
        }
    }
}

void dfs(int a[21][21], int d) {
    int cur = getmax(a);
    ans = max(ans, cur);
    
    if (d == 10) {
        return;
    }
    
    int rm = 10 - d;
    int mp = cur;
    for (int i = 0; i < rm; i++) {
        mp *= 2;
    }
    if (mp <= ans) {
        return;
    }
    
    for (int dir = 0; dir < 4; dir++) {
        int tb[21][21];
        copy(a, tb);
        
        if (dir == 0) up(tb);
        else if (dir == 1) down(tb);
        else if (dir == 2) left(tb);
        else right(tb);
        
        if (same(a, tb)) {
            continue;
        }
        
        dfs(tb, d + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
        }
    }
    
    dfs(b, 0);
    cout << ans << endl;
    
}