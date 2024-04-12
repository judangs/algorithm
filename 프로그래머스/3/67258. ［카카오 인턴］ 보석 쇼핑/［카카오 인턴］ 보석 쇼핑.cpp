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
    int start = 0, end = start, min_len = INT32_MAX;
    while(start <= end && end < gems.size()) {
        showcase[gems[end]]++;

        if(showcase.size() == total.size()) {
            while(showcase.size() == total.size()) {

                if(end - start < min_len) {
                    if(width.first == start && width.second == end)
                        return {start + 1, end + 1};
                    width.first = start;
                    width.second = end;
                    min_len = (end - start);
                }

                showcase[gems[start]]--;
                if(showcase[gems[start]] == 0) {
                    showcase.erase(showcase.find(gems[start]));
                }
                start++;
            }

            start = end;
            showcase.clear();
        }
        else
            end++;
    }

    vector<int> answer = {width.first + 1, width.second + 1};
    return answer;
}