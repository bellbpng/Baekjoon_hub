#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;


void UpdateDict(map<string, int>& dict, string msg, int index, vector<int>& answer){
    if(msg.size()==0) return;
    
    // 앞에서부터 문자열 파싱하기
    int len = 1;
    string str = string(1, msg[0]);
    for(int i=1; i<msg.length(); i++){
        str.push_back(msg[i]);
        if(dict.find(str)==dict.end()) {
            dict[str] = index;
            str.pop_back();
            break;
        }
        len++;
    }
    
    answer.push_back(dict[str]);
    string nmsg = msg.substr(len);
    UpdateDict(dict, nmsg, index+1, answer);
}

vector<int> solution(string msg) {
    vector<int> answer;
    
    // init
    map<string, int> dict;
    string alphabet; int index;
    for(int i=0; i<26; i++){
        alphabet = string(1, 'A'+i);
        dict[alphabet] = i+1;
    }
    
    UpdateDict(dict, msg, 27, answer);
    
    return answer;
}