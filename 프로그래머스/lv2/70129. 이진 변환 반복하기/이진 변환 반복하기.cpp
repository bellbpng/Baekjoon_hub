#include <string>
#include <vector>
#include <iostream>

using namespace std;

string convert_to_binary(int c){
    if(c/2 == 0) return "1";
    else return convert_to_binary(c/2) + to_string(c%2);
    
}

vector<int> solution(string s) {
    vector<int> answer(2,0); // answer[0]: 이진 변환 횟수, answer[1]: 제거된 0의 개수
    string x = s;
    int c = 0;
    while(c!=1){
        // 1. 0을 제거한다.
        string tmp;
        for(int i=0; i<x.length(); i++){
            if(x[i]=='0') answer[1]++;
            else tmp.push_back(x[i]);
        }
        
        // 2. c를 구하고 이진법으로 표현한 후 x를 갱신한다.
        c = tmp.length();
        x = convert_to_binary(c);
        answer[0]++;
    }
    
    return answer;
}