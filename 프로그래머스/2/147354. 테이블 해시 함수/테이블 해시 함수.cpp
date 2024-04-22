#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int pivot;

bool compare(vector<int> a, vector<int> b) {
    if(a[pivot-1] == b[pivot-1]) {
        return a[0] > b[0];
    }
    return a[pivot-1] < b[pivot-1];
}


int solution(vector<vector<int>> data, int col, int row_begin, int row_end) {
    pivot = col;
    sort(data.begin(), data.end(), compare);

    vector<int> xor_bit;
    for(int idx=row_begin; idx<=row_end; idx++) {
        int total = 0;
        for(int i=0; i<data[idx-1].size(); i++) {
            total += data[idx-1][i] % idx;
        }
        
        xor_bit.push_back(total);
    }

    int answer = xor_bit.front();
    for(int i=1; i<xor_bit.size(); i++) {
        answer ^= xor_bit[i];
    }

    return answer;
}