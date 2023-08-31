#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

string flipU(string u){
    string ret;
    for(int i=0; i<u.length(); i++){
        if(u[i]=='(') ret.push_back(')');
        else if(u[i]==')') ret.push_back('(');
    }
    return ret;
}

string convertString(string str){
    if(str.length()==0) return "";
    
    string u,v;
    stack<char> s;
    int flag = 1; // 0: 균형잡힌 괄호 문자열, 1: 올바른 괄호 문자열
    int leftCnt=0, rightCnt=0;
    int idx=0;
    // set u
    for(int i=0; i<str.length(); i++){
        if(str[i]=='(') {
            s.push(str[i]);
            leftCnt++;
        }
        else if(str[i]==')') {
            rightCnt++;
            if(s.size()==0) flag=0;
            else s.pop();
        }
        u.push_back(str[i]);
        if(leftCnt==rightCnt) {
            idx=i+1;
            break;
        }
    }
    cout << "u: " << u << endl;
    // set v
    for(int i=idx; i<str.length(); i++){
        v.push_back(str[i]);
    }
    
    if(flag==1) return u + convertString(v);
    else{
        string front = "(";
        front += convertString(v);
        front += ")";
        u = u.substr(1); // 첫번째 문자 제거
        u.pop_back(); // 마지막 문자 제거
        u = flipU(u);
        return front + u;
    }
}

string solution(string p) {
    string answer = "";
    bool correctFlag = true;
    stack<char> s;
    for(int i=0; i<p.length(); i++){
        if(p[i]=='(') s.push(p[i]);
        else if(p[i]==')'){
            if(s.size()==0) {
                correctFlag = false;
                break;
            }
            else s.pop();
        }
    }
    if(correctFlag) answer=p;
    else answer = convertString(p);
    
    return answer;
}