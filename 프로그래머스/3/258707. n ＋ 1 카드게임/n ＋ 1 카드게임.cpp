#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;

set<int> hand;
set<int> draw;

int draw_ptr = 0;

bool CompareHandWithHand(int n) {
    for(int current: hand) {
        if(hand.find(n - current) != hand.end()) {
            hand.erase(current);
            hand.erase(n - current);
            return true;
        }
    }

    return false;
}

bool CompareDrawWithHand(int n) {
    for(int current: hand) {
        if(draw.find(n - current) != draw.end()) {
            hand.erase(current);
            draw.erase(n - current);
            return true;
        }
    }

    return false;
}

bool CompareDrawWithDraw(int n) {
    for(int current: draw) {
        if(draw.find(n - current) != draw.end()) {
            draw.erase(current);
            draw.erase(n - current);
            return true;
        }
    }

    return false;
}

int solution(int coin, vector<int> cards) {
    int n = cards.size();

    for(int i=0; i<n/3; i++) hand.insert(cards[i]);

    int stage = 1;
    for(int current = n/3; current < n; current += 2) {
        draw.insert(cards[current]);
        draw.insert(cards[current + 1]);

        if(CompareHandWithHand(n + 1)) {
        }
        else if(coin >= 1 && CompareDrawWithHand(n + 1)) {
            coin -= 1;
        }
        else if(coin >= 2 && CompareDrawWithDraw(n + 1)) {
            coin -= 2;
        }
        else break;

        stage++;
    }

    return stage;
}