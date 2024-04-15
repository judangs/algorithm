#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool correct_tree(string tree, string skill, int idx) {
    for(int i=0; i<idx; i++) {
        if(tree.find(skill[i]) == string::npos)
            return false;
    }

    return true;
}

int solution(string skill, vector<string> skill_trees) {
    
    int answer = 0;
    for(string skill_tree: skill_trees) {
        int i = 0;
        for(i; i<skill_tree.size(); i++) {
            int idx;
            string compare = skill_tree.substr(0, i + 1);
            
            if((idx = skill.find(skill_tree[i])) != string::npos) {
                if(correct_tree(compare, skill, idx) == false)
                    break;
            }
        }
        
        if(i == skill_tree.size())
            answer++;
    }

    return answer;
}