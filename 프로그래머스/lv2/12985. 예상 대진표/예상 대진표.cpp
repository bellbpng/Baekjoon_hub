#include <iostream>

using namespace std;

int get_pow(int n){
    if(n/2==1) return 1;
    return 1+get_pow(n/2);
}

int solution(int n, int a, int b)
{
    int answer = 0;
    
    // init
    int power = get_pow(n);
    int p = 1, r = n;
    int q = (p+r)/2;
    
    int big = a>b ? a : b;
    int small = a<b ? a : b;
    
    while(true){
        if(small>=p && small<=q && big>=q+1 && big<=r){ // 서로 반대편에 있는 경우
            answer = power;
            break;
        }
        else if(small<=q) { // 왼쪽에 있는 경우
            r = q;
        }
        else if(small>=q+1) { // 오른쪽에 있는 경우
            p = q+1;
        }
        power--;
        q = (p+r)/2;
    }

    return answer;
}