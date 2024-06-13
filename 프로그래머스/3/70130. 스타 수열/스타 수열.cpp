#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> arr;

int get_sub_sequence_len(vector<int> & a, int max_dup_elem) {
    int answer = 0, flag = 0;
    for(int current = 0; current<a.size(); current++) {
        if(a[current] != max_dup_elem) flag = 1;
        else if(a[current] == max_dup_elem && flag == 1) {
            answer += 2;
            flag ^= 1;
        }
        else if(a[current] == max_dup_elem && flag == 0) {
            if(current + 1 < a.size()) {
                if(a[current + 1] != max_dup_elem) {
                    current++;
                    answer += 2;
                }
            }
        }
    }

    return answer;
}

int solution(vector<int> a) {
    arr.resize(a.size(), 0);
    for(int current: a) {
        arr[current]++;
    }

    int max_dup = *max_element(arr.begin(), arr.end());

    int answer = 0;
    for(int max_dup_elem=0; max_dup_elem<arr.size(); max_dup_elem++) {
        if(arr[max_dup_elem] > (answer / 2)) {
            answer = max(answer, get_sub_sequence_len(a, max_dup_elem));
        }
    }

    return answer;
}