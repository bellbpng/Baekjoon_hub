#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void get_pulse_array(vector<int>& sequence, vector<long long>& pulse1, vector<long long>& pulse2){
    int n=sequence.size();
    for(int i=0; i<n; i++){
        if(i%2==0){
            pulse1.push_back(sequence[i]);
            pulse2.push_back(sequence[i]*(-1));
        }
        else{
            pulse1.push_back(sequence[i]*(-1));
            pulse2.push_back(sequence[i]);
        }
    }
}

long long get_max_pulse(vector<long long>& pulse1, vector<long long>& pulse2){
    int n = pulse1.size();
    vector<long long> dp1(n+1,0), dp2(n+1,0);
    long long ret = -99999999;
    for(int i=1; i<=n; i++){
        dp1[i] = max(dp1[i-1]+(long long)pulse1[i-1], (long long)pulse1[i-1]);
        dp2[i] = max(dp2[i-1]+(long long)pulse2[i-1], (long long)pulse2[i-1]);
        ret = max(ret, dp1[i]);
        ret = max(ret, dp2[i]);
    }

    return ret;
}

long long solution(vector<int> sequence) {
    long long answer = 0;
    
    vector<long long> pulse1, pulse2;
    get_pulse_array(sequence, pulse1, pulse2);
    
    if(sequence.size()==1) // 길이가 1인 경우
        answer = max(pulse1[0], pulse2[0]);
    else
        answer = get_max_pulse(pulse1, pulse2);
    
    
    return answer;
}