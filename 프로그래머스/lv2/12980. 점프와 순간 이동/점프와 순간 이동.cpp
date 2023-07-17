#include <iostream>
using namespace std;

void get_min_energy(int n, int& ans){
    if(n==0) return;
    if(n%2==0) get_min_energy(n/2, ans);
    else {
        n--; ans++;
        get_min_energy(n/2, ans);
    }
}

int solution(int n)
{
    int ans = 0;
    get_min_energy(n, ans);

    return ans;
}