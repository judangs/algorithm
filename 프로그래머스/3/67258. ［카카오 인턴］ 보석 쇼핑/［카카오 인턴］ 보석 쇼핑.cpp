#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> gems) {
    set<string> total;
    for(string gem: gems) {
        total.insert(gem);
    }

    map<string, int> showcase;
    pair<int, int> width;
    int start = 0, end, min_len = INT32_MAX;
    for(end = 0; end<gems.size(); end++) {
        showcase[gems[end]]++;
        if(showcase.size() == total.size())
            break;
    }

    while(end < gems.size()) {

        if(end - start < min_len) {
            width.first = start;
            width.second = end;
            min_len = (end - start);
        }

        string find_key = gems[start];
        showcase[find_key]--;
        
        if(showcase[find_key] == 0) {
            for(end += 1; end<gems.size(); end++) {
                showcase[gems[end]]++;
                if(gems[end] == find_key)
                    break;
            }
        }

        start++;
    }

    return {width.first + 1, width.second + 1};
}