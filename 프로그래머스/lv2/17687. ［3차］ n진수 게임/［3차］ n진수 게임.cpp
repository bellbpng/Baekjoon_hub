#include <string>
#include <vector>
#include <iostream>

using namespace std;

string ConvToNexp(int n, int num){
    if(num == 0) return string(1, '0');
    if(num/n == 0) {
        int r = num%n;
        if(r>=10){
            r = 65 + (r-10);
            return string(1, r);
        }
        return to_string(r);
    }
    
    int r = num%n;
    if(r >= 10){
        r = 65 + (r - 10);
        return ConvToNexp(n, num/n) + string(1, r);
    }
    return ConvToNexp(n, num/n) + to_string(r);
}

void GetMathString(string& str, int len, int n, int num){
    if(str.size()>=len) return;
    
    str = str + ConvToNexp(n, num);
    GetMathString(str, len, n, num+1);
}

string solution(int n, int t, int m, int p) {
    string answer = "";
    int len = m * t;
    string str;
    GetMathString(str, len, n, 0);
    // cout << str << endl;
    
    for(int i=0; i<t; i++){
        answer.push_back(str[p-1 + m*i]);
    }
    
    return answer;
}