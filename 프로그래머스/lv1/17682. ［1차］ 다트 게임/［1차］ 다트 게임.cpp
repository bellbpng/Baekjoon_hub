#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

int solution(string dartResult) {
    int answer = 0;
    stringstream ss(dartResult);
    
    vector<int> scores(3, 0);
    int num;
    char bonus, option;
    for(int i=0; i<3; i++){
        ss >> num;
        bonus = ss.get();
        option = ss.get();
        
        if(option != '*' && option != '#')
            ss.unget(); // 버퍼의 커서를 앞으로 옮긴다.
        
        // 보너스
        if(bonus=='D') num = num*num;
        else if(bonus=='T') num = num*num*num;
        scores[i] = num;
        
        // 옵션
        if(option=='*'){
            if(i>0) scores[i-1] = scores[i-1] * 2;
            scores[i] = scores[i]*2;
        }
        else if(option=='#'){
            scores[i] = scores[i] * (-1);
        }
    }
    
    answer = scores[0] + scores[1] + scores[2];
    return answer;
}