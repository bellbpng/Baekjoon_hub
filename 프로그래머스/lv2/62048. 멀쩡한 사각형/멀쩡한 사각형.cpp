#include <iostream>
#include <algorithm>
using namespace std;

long long a, b;

double func(long long x){
    double ret = (b*x) / (double)a;
    return ret;
}

int GCD(int a, int b){
    if(a%b==0) return b;
    return GCD(b, a%b);
}

long long solution(int w,int h) {
    long long answer = 0;
    long long total = (long long)w * h;
    
    // 최대공약수 찾기
    int gcd = GCD(w,h);
    a = w / (long long)gcd;
    b = h / (long long)gcd;
    
    long long area = a*b;
    long long tmp = 0;
    for(long long i=1; i<a; i++){
        double val = func(i);
        tmp += (long long)val;
    }
    area -= (tmp*2); // 대칭 빼주기
    area *= (long long)gcd;
    answer = total - area;
    return answer;
}