#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int a, int b){
    return a<b;
}

int solution(vector<int> d, int budget) {
    int answer = 0;
    
    // 오름차순 정렬
    sort(d.begin(), d.end(), cmp);
    int i=0;
    while(budget-d[i] >= 0 && i < d.size()){
        budget -= d[i++];
        answer++;
    }
    
    return answer;
}