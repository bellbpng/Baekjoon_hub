#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

int cnt=0; // 실제 원소의 개수

bool cmp(int a, int b){
    return a<b;
}
void update_queue(string operations, deque<int>& deq){
    stringstream stm;
    stm.str(operations);
    char op; int num;
    stm >> op >> num;
    getchar();
    
    switch(op){
        case 'I':
            cnt++;
            deq.push_back(num);
            sort(deq.begin(), deq.end(), cmp);
            break;
        case 'D':
            if(num==-1){ // 최솟값을 지운다.
               if(deq.size()==0) break;
                deq.pop_front();
            }
            else if(num==1){ // 최댓값을 지운다.
               if(deq.size()==0) break;
                deq.pop_back();
            }
    }
}

vector<int> solution(vector<string> operations) {
    vector<int> answer;
    
    deque<int> deq;
    
    for(int i=0; i<operations.size(); i++){
        update_queue(operations[i], deq);
    }
    
    if(deq.size()==0){
        answer.push_back(0);
        answer.push_back(0);
    }
    else{
        answer.push_back(deq.back());
        answer.push_back(deq.front());
    }
    
    return answer;
}