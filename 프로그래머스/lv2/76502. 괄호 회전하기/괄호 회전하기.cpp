#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int check_correct_string(string str){
    stack<char> s;
    
    for(int i=0; i<str.length(); i++){
        if(str[i]=='(' || str[i]=='{' || str[i]=='[')
            s.push(str[i]);
        else if(str[i]==')'){
            if(s.empty()) return 0;
            else if(s.top()=='(') s.pop();
            else return 0;
        }
        else if(str[i]=='}'){
            if(s.empty()) return 0;
            else if(s.top()=='{') s.pop();
            else return 0;
        }
        else if(str[i]==']'){
            if(s.empty()) return 0;
            else if(s.top()=='[') s.pop();
            else return 0;
        }
    }
    
    if(s.empty()) return 1;
    else return 0;
}

int solution(string s) {
    int answer = 0;
    
    string str = s;
    answer += check_correct_string(str);
    for(int i=1; i<s.length(); i++){
        char first_ch = s[0];
        str = s.substr(1);
        str.push_back(first_ch);
        answer += check_correct_string(str);
        s = str;
    }
    
    return answer;
}