#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(string str1, string str2) {
    int answer = 0;
    // init
    // 가능한 모든 조합
    vector<int> set_1(26*26, 0);
    vector<int> set_2(26*26, 0);
    
    for(int i=0; i<str1.size(); i++){
        if(isalpha(str1[i]) && isalpha(str1[i+1])){
            if(isupper(str1[i])) str1[i]=tolower(str1[i]);
            if(isupper(str1[i+1])) str1[i+1]=tolower(str1[i+1]);
            set_1[(str1[i]-'a')*26 + (str1[i+1]-'a')]++;
        }
    }
    
    for(int i=0; i<str2.size(); i++){
        if(isalpha(str2[i]) && isalpha(str2[i+1])){
            if(isupper(str2[i])) str2[i]=tolower(str2[i]);
            if(isupper(str2[i+1])) str2[i+1]=tolower(str2[i+1]);
            set_2[(str2[i]-'a')*26 + (str2[i+1]-'a')]++;
        }
    }
    
    int inter_cnt = 0, union_cnt=0;
    for(int i=0; i<set_1.size(); i++){
        inter_cnt += min(set_1[i], set_2[i]);
        union_cnt += max(set_1[i], set_2[i]);
    }
    if(union_cnt==0) 
        answer = 65536;
    else
        answer = int(((float)inter_cnt/union_cnt) * 65536);
    
    return answer;
}