#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

bool check_palindrome(string& str, int len, int start, int end){
    for(int i=0; i<len/2; i++){
        if(str[start+i] != str[end-i])
            return false;
    }
    return true;
}

bool get_longest_palindrome(string& str, int substr_len){
    int orgstr_len = str.length();
    int diff = orgstr_len - substr_len;
    
    int start = 0, end = orgstr_len-1;
    int front, back;
    for(int i=0; i<=diff; i++){
        front = start + i;
        back = end - (diff-i);
        if(check_palindrome(str, substr_len, front, back))
            return true;
    }
    return false;
}

// 모든 경우의 수를 탐색하는 것이 아니라 길이가 최대인 팰린드롬부터 찾는다.
int solution(string s)
{
    int answer=0;
    int n = s.length();
    
    for(int substr_len=n; substr_len>0; substr_len--){
        if(get_longest_palindrome(s, substr_len)) {
            answer = substr_len;
            return answer;
        }
    }
    
    answer=1;
    return answer;
}