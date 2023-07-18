#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>

using namespace std;

vector<int> board[1001];

void set_elements_on_board(string s){
    vector<int> v;
    string str;
    for(int i=0; i<s.length(); i++){
        if(s[i] != '{' && s[i] != '}' && s[i] != ','){
            str.push_back(s[i]);
        }
        else if(s[i]==',' && str.size()>0){
            v.push_back(stoi(str));
            str.clear();
        }
        else if(s[i]=='}' && str.size()>0){
            v.push_back(stoi(str));
            str.clear();
            int len = v.size();
            for(int i=0; i<len; i++)
                board[len].push_back(v[i]);
            v.clear();
        }
    }
}

vector<int> solution(string s) {
    vector<int> answer;
    
    // init
    s = s.substr(1);
    s.pop_back();
    set_elements_on_board(s);
    
    int n = 1;
    while(true){
        if(board[n].size()==0) break;
        for(int i=0; i<board[n].size(); i++){
            if(find(answer.begin(), answer.end(), board[n][i]) == answer.end()){
                answer.push_back(board[n][i]);
            }
        }
        n++;
    }
    
    return answer;
}