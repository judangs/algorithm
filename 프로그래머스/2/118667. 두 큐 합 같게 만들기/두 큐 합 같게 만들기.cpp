#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> queue1, vector<int> queue2) {
    
    long long queue1_sum = 0, queue2_sum = 0;
    for(int q1: queue1) queue1_sum += q1;
    for(int q2: queue2) queue2_sum += q2;

    int size = queue1.size();

    int sum = (queue1_sum + queue2_sum) / 2;

    int answer = 0, max_answer = 4 * size;
    int ptr1 = 0, ptr2 = 0;
    while(queue1_sum != queue2_sum) {

        if(answer > max_answer) return -1;
        
        if(queue1_sum > queue2_sum) {
            if(ptr1 >= size) {
                queue1_sum -= queue2[ptr1 % size];
                queue2_sum += queue2[ptr1++ % size];
            }
            else {
            queue1_sum -= queue1[ptr1];
            queue2_sum += queue1[ptr1++];
            }
        }
        else {
            if(ptr2 >= size) {
                queue2_sum -= queue1[ptr2 % size];
                queue1_sum += queue1[ptr2++ % size];
            }
            else {
            queue2_sum -= queue2[ptr2];
            queue1_sum += queue2[ptr2++];
            }
        }
        
        answer++;
    }

    return answer;
}