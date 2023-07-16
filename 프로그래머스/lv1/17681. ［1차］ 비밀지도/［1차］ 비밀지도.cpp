#include <string>
#include <vector>
#include <iostream>

using namespace std;

string get_to_bin(int n){
    if(n==0) return string("0");
    if(n/2==0) return string("1");
    else return get_to_bin(n/2) + to_string(n%2);
}

void set_size(string& s1, string& s2, int n){
    string tmp;
    if(s1.size()<n){
        for(int i=0; i<n-s1.size(); i++)
            tmp.push_back('0');
        s1 = tmp + s1;
    }
    tmp.clear();
    if(s2.size()<n){
        for(int i=0; i<n-s2.size(); i++)
            tmp.push_back('0');
        s2 = tmp + s2;
    }
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    
    for(int i=0; i<n; i++){
        string s1 = get_to_bin(arr1[i]);
        string s2 = get_to_bin(arr2[i]);
        set_size(s1, s2, n);
        
        string decoder;
        for(int j=0; j<n; j++){
            if(s1[j]=='0' && s2[j]=='0')
                decoder.push_back(' ');
            else
                decoder.push_back('#');
        }
        answer.push_back(decoder);
    }
    
    return answer;
}