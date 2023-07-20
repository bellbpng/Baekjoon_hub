#include <string>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// k진수 변환
string GetExpressK(int n, int k){
    if(n/k==0) return to_string(n%k);
    else return GetExpressK(n/k, k) + to_string(n%k);
}

bool check_prime(long long n){
    if(n==1) return false;
    if(n==2) return true;
    if(n%2==0) return false;
    
    for(int i=3; i<=sqrt(n); i+=2){
        if(n%i==0) return false;
    }
    return true;
}

int solution(int n, int k) {
    int answer = 0;
    
    string numStrK = GetExpressK(n,k);
    int len = numStrK.length();
    string str;
    vector<long long> cand;
    for(int i=0; i<len; i++){
        if(numStrK[i]!='0'){
            str.push_back(numStrK[i]);
        }
        else if(numStrK[i]=='0'){
            if(str.size()>0){
                cand.push_back(stoll(str));
                str.clear();
            }
        }
        
        if(i==len-1){
            if(str.size()>0){
                cand.push_back(stoll(str));
                str.clear();
            }
        }
    }
    
    for(auto ele:cand){
        if(check_prime(ele)) answer++;
    }
    
    return answer;
}