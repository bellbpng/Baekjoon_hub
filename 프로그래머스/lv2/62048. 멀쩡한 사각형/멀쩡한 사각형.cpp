#include <iostream>
#include <algorithm>
using namespace std;

long long a, b;

double func(long long x){
    double ret = (b*x) / (double)a;
    return ret;
}

long long solution(int w,int h) {
    long long answer = 0;
    long long total = (long long)w * h;
    
    // 최대공약수 찾기
    long long small = min(w, h);
    long long mCommon = 1; // 서로소인 경우 1
    for(long long i=2; i<=small; i++){
        if(w%i==0 && h%i==0) mCommon = i;
    }
    a = w / mCommon;
    b = h / mCommon;
    long long area = 0;
    if(b%a==0){
        area = h;
    }
    else{
        area = a*b;
        long long tmp = 0;
        for(long long i=1; i<a; i++){
            double val = func(i);
            tmp += (long long)val;
        }
        area -= (tmp*2); // 대칭 빼주기
        area *= mCommon;
    }
    answer = total - area;
    return answer;
}