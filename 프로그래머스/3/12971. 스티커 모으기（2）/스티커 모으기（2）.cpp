#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> sticker) {
    vector<int> first(sticker.size(), 0);
    vector<int> second(sticker.size(), 0);

    if(sticker.size() == 1)
        return sticker.front();
        
    int end = sticker.size() - 1;

    first[0] = sticker[0];
    first[1] = first[0];
    for(int i=2; i<end; i++) {
        first[i] = max(first[i - 2] + sticker[i], first[i - 1]);
    }
    
    second[1] = sticker[1];
    for(int i=2; i<sticker.size(); i++) {
        second[i] = max(second[i - 2] + sticker[i], second[i - 1]);
    }

    return max(first[end - 1], second[end]);

}