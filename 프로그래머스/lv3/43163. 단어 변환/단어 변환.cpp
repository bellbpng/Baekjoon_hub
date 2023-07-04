#include <string>
#include <vector>
#include <algorithm>

#define INF 100
using namespace std;


bool check_words(vector<string>& words, string& target){
    for(auto str:words){
        if(target==str)
            return true;
    }
    return false;
}

bool check_change_alphabet(string& cstr, string& nstr){
    int len = cstr.length();
    int cnt = 0;
    for(int i=0; i<len; i++){
        if(cstr[i]!=nstr[i]) cnt++;
        if(cnt>1) return false;
    }
    return true;
}

// cstr: 현재 바꾼 문자열, bstr: 바꾸기 이전 문자열
int change_alphabet(string cstr, string bstr, string& target, int cnt, vector<bool>& visited, vector<string>& words){
    // 기저사례1: 바꾼 단어가 알파벳 하나만 변한 것이 아닌 경우
    if(check_change_alphabet(cstr, bstr)==false) return INF;
    // 기저사례2: target과 일치하는 경우
    if(cstr == target) return cnt;
    
    int ret = INF;
    for(int i=0; i<words.size(); i++){
        if(visited[i]==true) continue;
        visited[i] = true;
        string bstr = cstr;
        string cstr = words[i];
        ret = min(ret, change_alphabet(cstr, bstr, target, cnt+1, visited, words));
        visited[i] = false;
    }
    return ret;
}


int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    
    if(check_words(words, target)==false)
        return answer;
    
    int n = words.size();
    vector<bool> visited(n,false);
    string nstr = begin;
    nstr[0] = ' ';
    answer = change_alphabet(begin, nstr, target, 0, visited, words);
    if(answer==INF) answer = 0;
    
    return answer;
}