#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> memories;

int fabonacci(int current) {
    if(current <= 1) 
        return current;
    if(memories[current] != 0)
        return memories[current];
    return (memories[current] = (fabonacci(current - 1) + fabonacci(current - 2)) % 1234567);
}

int solution(int n) {
    memories.resize(n + 1, 0);
    return fabonacci(n);
}