#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <iostream>


using namespace std;

vector<int> eratos;
vector<bool> visit;
set<int> answer;

void dfs(int depth, int count, string numbers, string tmp) {
    if(depth == count) {
        if(eratos[stoi(tmp)] == true) {
            cout << tmp << endl;
            answer.insert(stoi(tmp));
        }
        return;
    }

    for(int i=0; i<numbers.size(); i++) {
        if(visit[i] == false) {
            visit[i] = true;
            dfs(depth + 1, count, numbers, tmp + numbers[i]);
            visit[i] = false;
        }
    }
}

void make_eratos() {
    for(int i=2; i<eratos.size(); i++) {
        for(int j=i; j<eratos.size(); j+=i) {
            if((j > i) && (j % i == 0))
                eratos[j] = 0;
        }
    }
}

int solution(string numbers) {
    
    visit.resize(numbers.size(), false);

    eratos.resize(9999999, 1);
    eratos[0] = 0;
    eratos[1] = 0;
    make_eratos();

    for(int i=1; i<=numbers.size(); i++) {
        dfs(0, i, numbers, "");
    }

    return answer.size();
}