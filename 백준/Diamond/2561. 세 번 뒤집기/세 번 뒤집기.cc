#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
bool solve = false;
vector<int> target;
vector<pair<int, int>> ans;
vector<pair<int, int>> now;

void play(int count, vector<int> & num);

vector<pair<int, int>> split(const vector<int>& arr) {
    vector<pair<int, int>> ret;
    for(int l = 0; l < N; ) {
        if(l == N - 1) {
            ret.push_back({l, l});
            break;
        }
        
        int r = l;
        int diff = arr[l + 1] - arr[l];
        
        if(abs(diff) == 1) {
            while(r + 1 < N && arr[r + 1] - arr[r] == diff) {
                r++;
            }
        }
        
        ret.push_back({l, r});
        l = r + 1;
    }
    return ret;
}

void reverse_array(int count, int l, int r, vector<int> & num) {
    reverse(num.begin() + l, num.begin() + r + 1);
    now.push_back({l + 1, r + 1});
    play(count + 1, num);
    reverse(num.begin() + l, num.begin() + r + 1);
    now.pop_back();
}

void play(int count, vector<int> & num) {
    if(solve) return;
    
    if(num == target) {
        ans = now; 
        solve = true;
        return;
    }

    if(count == 3) return;

    vector<pair<int, int>> ranges = split(num);

    for(int i = 0; i < ranges.size(); i++) {
        for(int j = i; j < ranges.size(); j++) {

            int sl, sr, el, er;
            tie(sl, sr) = ranges[i], tie(el, er) = ranges[j];
            
            reverse_array(count, sl, el, num);
            reverse_array(count, sl, er, num);
            reverse_array(count, sr, el, num);
            reverse_array(count, sr, er, num);
            
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<int> num(N);
    target.resize(N);
    
    for(int i = 0; i < N; i++) {
        cin >> num[i];
    }
    
    for(int i = 0; i < N; i++) {
        target[i] = i + 1;
    }

    play(0, num);
    
    while(ans.size() < 3) {
        ans.push_back({1, 1});
    }

    for(auto& [l, r]: ans) {
        cout << l << " " << r << endl;
    }
}
