#include <string>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

string get_reverse_tribin(int n){
    if(n/3==0) return to_string(n%3);
    else return to_string(n%3) + get_reverse_tribin(n/3);
}

int get_decimal_from_tri(string tri_str){
    int ret = 0;
    int diff = '0';
    int len = tri_str.length();
    for(int i=0; i<len; i++){
        ret += ((tri_str[len-1-i] - diff) * pow(3, i));
    }
    return ret;
}

int solution(int n) {
    int answer = 0;
    string tri_str = get_reverse_tribin(n);
    answer = get_decimal_from_tri(tri_str);
    return answer;
}