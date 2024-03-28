#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


bool compare(pair<string, int> a, pair<string, int> b) {
    return a.second < b.second;
}

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;
    
    vector<string> cache(cacheSize);
    
    for(string city: cities) {
        transform(city.begin(), city.end(), city.begin(), ::tolower);
        

        if(find(cache.begin(), cache.end(), city) != cache.end()) {
            answer += 1;
        }
        else {
            answer += 5;
        }
        
        
        // cache change
        if(cache.size() < cacheSize) cache.push_back(city);
        else {
            auto iter = find(cache.begin(), cache.end(), city);
            if(iter != cache.end()) {
                cache.push_back(city);
                cache.erase(iter);
            }
            else {
                cache.push_back(city);
                cache.erase(cache.begin());                
            }

        }
        
    }
    
    return answer;
}