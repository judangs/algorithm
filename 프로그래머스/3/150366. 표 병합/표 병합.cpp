#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

vector<vector<string>> board;
vector<int> arr(2500, 0);

vector<string> parse_command(string command) {
    vector<string> ret;
    stringstream iss(command);
    string buffer;
    while(getline(iss, buffer, ' ')) {
        ret.push_back(buffer);
    }

    return ret;
}

int find(int start) {
    if(start == arr[start])
        return arr[start];
    return (arr[start] = find(arr[start]));
}

void union_find(int a, int b) {
    a = find(a);
    b = find(b);
    
    if(a != b) {
        arr[b] = a;
    }
}

vector<string> solution(vector<string> commands) {
    
    for(int i=0; i<arr.size(); i++) {
        arr[i] = i;
    }
    board.resize(50, vector<string>(50, "EMPTY"));

    vector<string> answer;
    for(string command: commands) {
        vector<string> parse = parse_command(command);
        
        if(parse.front() == "UPDATE") {
            if(parse.size() == 4) {
                int y = stoi(parse[1]) - 1;
                int x = stoi(parse[2]) - 1;
                
                int parent = find(50 * y + x);
                board[parent/50][parent%50] = parse.back();
            }
            else {
                for(int i=0; i<board.size(); i++) {
                    for(int j=0; j<board[0].size(); j++) {
                        if(board[i][j] == parse[1] && arr[50 * i + j] == 50 * i + j) {
                            board[i][j] = parse.back(); 
                        }
                    }
                }
            }
        }
        else {
            int y = stoi(parse[1]) - 1;
            int x = stoi(parse[2]) - 1;

            if(parse.front() == "MERGE") {
                int next_y = stoi(parse[3]) - 1;
                int next_x = stoi(parse[4]) - 1;
                union_find(find(50 * y + x), find(50 * next_y + next_x));
                board[next_y][next_x] = "EMPTY";
            }
            else if(parse.front() == "UNMERGE") {
                int parent = find(50 * y + x);
                string recover = board[parent / 50][parent % 50];
                for(int i=0; i<arr.size(); i++) {
                    if(find(i) == parent) {
                        arr[i] = i;
                        board[i/50][i%50] = "EMPTY";
                    }
                }
                board[y][x] = recover;
            }
            else {
                int parent = find(50 * y + x);
                answer.push_back(board[parent/50][parent%50]);
            }
        }
    }
    return answer;
}