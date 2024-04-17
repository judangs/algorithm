#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(int brown, int yellow) {
    
    for(int width=1; width<=yellow; width++) {
        for(int height=1; height<=width; height++) {
            if(width * height == yellow) {
                if((width + 2) * (height + 2) - yellow == brown) {
                    return {width + 2, height + 2};
                }
            }
        }
    }
}