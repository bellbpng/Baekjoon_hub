#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    vector<int> answer;
    
    int number = 0, turn = 0;
    vector<string> history;
    for(int i=0; i<words.size(); i++){
        // 마지막 문자로 시작하는 단어를 말하지 않은 경우
        if(history.size()>0){
            string last = history.back();
            char last_ch = last.back();
            if(last_ch != words[i][0]){
                number = i%n + 1;
                turn = i/n+1;
                break;
            }
        }
        
        if(find(history.begin(), history.end(), words[i])==history.end()){
            history.push_back(words[i]);
        }
        else { // 이전에 등장한 단어를 사용한 경우
            number = i%n + 1;
            turn = i/n + 1;
            break;
        }
    }
    
    answer.push_back(number);
    answer.push_back(turn);
    return answer;
}