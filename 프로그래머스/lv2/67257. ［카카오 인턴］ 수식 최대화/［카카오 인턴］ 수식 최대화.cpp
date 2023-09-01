#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

vector<string> candOp = {"+-*", "+*-", "-+*", "-*+", "*+-", "*-+"};

long long getValue(string prior, vector<char>& top, vector<long long>& tnums){
    for(int j=0; j<3; j++){
        int idx=0;
        char pr = prior[j];
        for(int t=0; t<top.size(); t++){
            if(pr==top[t]){
                if(pr=='+') tnums[t] += tnums[t+1];
                else if(pr=='-') tnums[t] -= tnums[t+1];
                else if(pr=='*') tnums[t] *= tnums[t+1];
                tnums.erase(tnums.begin()+t+1);
                top.erase(top.begin()+t);
                t--;
            }
        }
    }
    return abs(tnums[0]);
}

long long solution(string expression) {
    long long answer = 0;
    vector<char> op;
    vector<long long> nums;
    string tmp;
    for(int i=0; i<expression.length(); i++){
        char ch = expression[i];
        if(isdigit(ch)) tmp.push_back(ch);
        else {
            nums.push_back(stoll(tmp));
            tmp.clear();
            op.push_back(ch);
        }
    }
    nums.push_back(stoll(tmp));
    
    for(int i=0; i<6; i++){
        vector<char> top = op;
        vector<long long> tnums = nums;
        string prior = candOp[i];
        answer = max(answer, getValue(prior, top, tnums));
        // cout << answer << endl;
    }
    
    return answer;
}