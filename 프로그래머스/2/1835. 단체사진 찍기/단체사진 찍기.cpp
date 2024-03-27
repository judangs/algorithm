#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

string member;
bool visit[8];
int result;

vector<char> arr;


void permutation(int depth, vector<string> & data) {
    if(depth == member.size()) {

        for(string option: data) {
            char first_m = option[0];
            char second_m = option[2];
            int f_idx = find(arr.begin(), arr.end(), first_m) - arr.begin();
            int s_idx = find(arr.begin(), arr.end(), second_m) - arr.begin();
            int distance = f_idx - s_idx;
            if(distance < 0) distance *= -1;
            switch(option[3]) {
                case '=':
                    if(distance != (option[4] - '0') + 1) return;
                    break;
                case '>':
                    if(distance <= (option[4] - '0') + 1) return;
                    break;
                case '<':
                    if(distance >= (option[4] - '0') + 1) return;
                    break;
            }
        }
        
        result++;
    }
    
    for(int i=0; i<member.size(); i++) {
        if(visit[i] == false) {
            visit[i] =true;
            arr.push_back(member[i]);
            permutation(depth + 1, data);
            arr.pop_back();
            visit[i] = false;
        }
    }
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<string> data) {

    for(int i=0; i<8; i++) visit[i] = false;
    result = 0;
    member = "ACFJMNRT";
    
    permutation(0, data);
    
    
    return result;
}
