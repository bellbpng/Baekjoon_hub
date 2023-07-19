#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

vector<string> init_set(string str){
    vector<string> str_set;
    string tmp;
    for(int i=0; i<str.size(); i++){
        if(isalpha(str[i])){
            if(isupper(str[i]))
                tmp.push_back(tolower(str[i]));
            else
                tmp.push_back(str[i]);
        }
       if(isalpha(str[i+1])){
            if(isupper(str[i+1]))
                tmp.push_back(tolower(str[i+1]));
            else
                tmp.push_back(str[i+1]);
        }
        if(tmp.size()==2)
            str_set.push_back(tmp);
        tmp.clear();
    }
    return str_set;
}

float get_jacard(vector<string>& short_set, vector<string>& long_set){
    int inter_count = 0;
    int union_count = 0;
    float ret = 0.0f;
    int long_len = long_set.size();
    int short_len = short_set.size();
    vector<int> checked(long_len, 0);
    vector<int> checked_s(short_len, 0);
    
    string ref;
    for(int i=0; i<short_set.size(); i++){
        ref = short_set[i];
        for(int j=0; j<long_set.size(); j++){
            if(ref==long_set[j] && checked[j]==0){
                inter_count++;
                checked[j]=1;
                checked_s[i]=1;
                break;
            }
        }
    }
    
    union_count = inter_count;
    for(int i=0; i<short_set.size(); i++){
        if(checked_s[i]==0)
            union_count++;
    }
    for(int i=0; i<long_set.size(); i++){
        if(checked[i]==0)
            union_count++;
    }
    ret = (float)inter_count / union_count;
    
    return ret;
}


int solution(string str1, string str2) {
    int answer = 0;
    // init
    vector<string> str1_set = init_set(str1);
    vector<string> str2_set = init_set(str2);   
    vector<string> short_set = str1_set < str2_set ? str1_set : str2_set;
    vector<string> long_set = str1_set > str2_set ? str1_set : str2_set;
    
    // A=B
    if(short_set == long_set) return 65536;
    
    float jacard = get_jacard(short_set, long_set);
    answer = int(jacard * 65536);
    
    return answer;
}