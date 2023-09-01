#include <string>
#include <vector>
#include <cctype>
#include <memory.h>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

vector<char> allCase, cand, op;
vector<long long> num;
long long ans = 0, result = 0;
bool visited[3] = {false, };

// 숫자가 작을수록 높은 우선순위
int getPriority(char oper){
    for(int i=0; i<cand.size(); i++){
        if(cand[i]==oper) return i;
    }
}

void getResult(vector<char> iop, vector<long long> inum){
    if(iop.size()==0) {
        result = abs(inum[0]);
        cout << result << endl;
        return;
    }
    
    vector<char> nop;
    vector<long long> nnum;
    // 가장 높은 우선순위 연산자 찾기
    int priority = getPriority(iop[0]);
    for(int i=1; i<iop.size(); i++){
        int np = getPriority(iop[i]);
        if(priority > np) priority = np;
    }
    
    bool flag = true;
    long long val;
    int idx = 0;
    for(int i=0; i<iop.size(); i++){
        if(priority==getPriority(iop[i]) && flag){
            if(iop[i]=='+') val = inum[idx] + inum[idx+1];
            else if(iop[i]=='-') val = inum[idx] - inum[idx+1];
            else if(iop[i]=='*') val = inum[idx] * inum[idx+1];
            nnum.push_back(val);
            idx+=2;
            flag = false;
        }
        else{
            nnum.push_back(inum[idx++]);
            nop.push_back(iop[i]);
        }
    }
    
    getResult(nop, nnum);
}

void setPriority(int v){
    if(cand.size()==allCase.size()) {
        // 수식 계산
        vector<char> iop = op;
        vector<long long> inum = num;
        getResult(iop, inum);
        ans = max(ans, result);
        return;
    }
    
    for(int i=0; i<allCase.size(); i++){
        if(visited[i]) continue;
        visited[i]=true;
        cand.push_back(allCase[i]);
        setPriority(i+1);
        cand.pop_back();
        visited[i]=false;
    }
}

long long solution(string expression) {
    long long answer = 0;
    
    // 0: +, 1: -, 2: *
    vector<char> opCount(3,0);
    string tmp;
    for(int i=0; i<expression.length(); i++){
        char ch = expression[i];
        if(isdigit(ch)) tmp.push_back(ch);
        else {
            num.push_back(stoll(tmp));
            tmp.clear();
            op.push_back(ch);
            if(ch=='+') opCount[0]++;
            else if(ch=='-') opCount[1]++;
            else if(ch=='*') opCount[2]++;
        }
    }
    num.push_back(stoll(tmp));
    if(opCount[0]>0) allCase.push_back('+');
    if(opCount[1]>0) allCase.push_back('-');
    if(opCount[2]>0) allCase.push_back('*');
    
    setPriority(0);
    answer = ans;
    return answer;
}