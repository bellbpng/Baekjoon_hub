#include <string>
#include <cctype>
#include <iostream>
#include <vector>

using namespace std;

int solution(string dartResult) {
    int answer = 0;
    
    vector<int> scores(3,0);
    string str;
    int idx = 0;
    for(int i=0; i<dartResult.size(); i++){
        char ch = dartResult[i];
        if(isdigit(ch)){
            str.push_back(ch);
        }
        else if(ch=='S' || ch=='D' || ch=='T'){
            int num = stoi(str);
            str.clear();
            if(ch=='D') num = num*num;
            else if(ch=='T') num = num*num*num;
            scores[idx] = num;
            
            // 스타상, 아차상 확인
            if(i==dartResult.size()-1) continue;
            char nCh = dartResult[i+1];
            if(nCh=='*'){
                if(idx>0) scores[idx-1] = scores[idx-1] * 2;
                scores[idx] = scores[idx] * 2;
                i++;
            }
            else if(nCh=='#'){
                scores[idx] = scores[idx] * (-1);
                i++;
            }
            idx++;
        }
    }
    
    answer = scores[0] + scores[1] + scores[2];
    return answer;
}