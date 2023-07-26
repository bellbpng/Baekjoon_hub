#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

vector<string> solution(vector<string> record) {
    vector<string> answer;
    
    stringstream ss;
    string state, userID, name;
    map<string, string> table; // userID 별 name 테이블
    vector<pair<string, string>> msgList; // userID 별 state 로 msg 기록
    for(int i=0; i<record.size(); i++){
        ss.clear();
        ss.str(record[i]);
        ss >> state >> userID;
        if(state=="Leave"){
            msgList.push_back(make_pair(userID, state));
            continue;
        }
        ss >> name;
        if(state=="Enter"){
            table[userID] = name;
            msgList.push_back(make_pair(userID, state));
        }
        else if(state=="Change"){
            table[userID] = name;
        }
    }
    
    string msg;
    for(int i=0; i<msgList.size(); i++){
        userID = msgList[i].first;
        state = msgList[i].second;
        name = table[userID];
        msg = name + string("님이 ");
        if(state=="Enter")
            msg += string("들어왔습니다.");
        else if(state=="Leave")
            msg += string("나갔습니다.");
        answer.push_back(msg);
    }
    
    return answer;
}