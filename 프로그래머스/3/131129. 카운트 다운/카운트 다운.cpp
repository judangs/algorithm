#include <string>
#include <vector>
#include <iostream>

using namespace std;

// dp 테이블
vector<pair<int, int>> dp;
vector<pair<int, int>> table;


bool compare(pair<int, int> a, pair<int, int> b) {
    if(a.first == b.first) {
        return a.second < b.second;
    }
    return a.first > b.first;
}

vector<int> solution(int target) {
    
    dp.resize(target + 1, {INT32_MAX, 0});
    table.resize(61, {-1, -1});
    
    // 싱글
    for(int score=1; score<=20; score++) {
        table[score] = {1, 1};
    }
    // 더블
    for(int score=22; score<=40; score+=2) {
        table[score] = {1, 0};
    }
    // 트리플
    for(int score=21; score<=60; score+=3) {
        table[score] = {1, 0};
    }
    
    table[50] = {1, 1};  
    
    dp[0] = {0, 0};
    
    if(target <=60 && table[target].first != -1)  {
        return {table[target].first, table[target].second};
    }
    
    
    for(int current=1; current<=target; current++) {
        for(int score=1; score<=60; score++) {
            // 이전 dp 테이블이 채워져 있는 경우라면?
            if(current - score >= 0 &&  table[score].first != -1) {
                
                pair<int, int> next = { dp[current - score].first + 1, dp[current - score].second + table[score].second};
                if(compare(dp[current], next) == true) {
                    dp[current] = next;
                }
            }
        }
    }
    
    vector<int> answer = {dp[target].first, dp[target].second};
    return answer;
}