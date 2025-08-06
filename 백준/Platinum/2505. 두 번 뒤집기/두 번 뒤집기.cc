#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
bool solve = false;
vector<pair<int, int>> ranges;
vector<pair<int, int>> answer;

void solved(int count, vector<int> & number, vector<int> & target) {

    if(number == target) {
        solve = true;
        answer = ranges;
        return;
    }

    if(count == 2) return;
    if(solve) return;

    for(int i=0, l; i<N; i++) {
        if(number[i] != i + 1) {
            l = i;
            for(int r=l; r<N; r++) {
                if(number[r] == i + 1) {
                    reverse(number.begin() + l, number.begin() + r + 1);
                    ranges.push_back({l + 1, r + 1});
                    solved(count + 1, number, target);
                    reverse(number.begin() + l, number.begin() + r + 1);
                    ranges.pop_back();
                }
            }

            break;
        }
    }

    for(int i=N-1, r; 0 <= i; i--) {
        if(number[i] != i + 1) {
            r = i;
            for(int l=r; 0 <= l; l--) {
                if(number[l] == i + 1) {
                    reverse(number.begin() + l, number.begin() + r + 1);
                    ranges.push_back({l + 1, r + 1});
                    solved(count + 1, number, target);
                    reverse(number.begin() + l, number.begin() + r + 1);
                    ranges.pop_back();  
                }
            }

            break;
        }
    }

}


int main() {

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    cin >> N;
    vector<int> number(N);
    for(auto & num: number) cin >> num;

    vector<int> target(N);
    for(int i=0; i<N; i++) target[i] = i + 1;

    solved(0, number, target);
    while(answer.size() < 2)
        answer.push_back({1, 1});

    for(auto & [l, r]: answer) {
        cout << l << " " << r << endl;
    }

}