#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

bool cmp(int a, int b){
    return a>b;
}

long long solution(int n, vector<int> works) {
    long long answer = 0;
    
    int total_load = 0;
    for(int i=0; i<works.size(); i++){
        total_load += works[i];
    }
    
    // 야근을 할 필요가 없는 경우
    if(total_load <= n) return answer;
    
    priority_queue<int> pq; // max heap
    for(auto ele:works)
        pq.push(ele);
    
    int ele;
    while(n>0){
        ele = pq.top();
        pq.pop();
        pq.push(ele-1);
        n -= 1;
    }
    
   while(!pq.empty()){
       ele = pq.top();
       pq.pop();
       answer += ele*ele;
   }
    
    return answer;
}