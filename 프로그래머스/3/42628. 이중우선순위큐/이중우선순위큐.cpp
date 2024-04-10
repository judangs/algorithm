#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(vector<string> operations) {
    
    vector<int> custom_queue;
    string buffer;
    for(string operation: operations) {
        stringstream iss(operation);
        getline(iss, buffer, ' ');
        if(buffer == "I") {
            getline(iss, buffer, ' ');
            custom_queue.push_back(stoi(buffer));
        }
        else {
            if(custom_queue.empty())
                continue;

            getline(iss, buffer, ' ');
            if(stoi(buffer) == 1) {
                auto iter = max_element(custom_queue.begin(), custom_queue.end());
                custom_queue.erase(iter);
            }
            else {
                auto iter = min_element(custom_queue.begin(), custom_queue.end());
                custom_queue.erase(iter);
            }
        }
    }

    if(custom_queue.size() == 0) {
        return {0, 0};
    }

    vector<int> answer(2);
    answer[0] = *max_element(custom_queue.begin(), custom_queue.end());
    answer[1] = *min_element(custom_queue.begin(), custom_queue.end());

    return answer;
}