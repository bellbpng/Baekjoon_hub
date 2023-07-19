#include <vector>
#include <iostream>
using namespace std;

vector<int> primes(3000, 1);

int get_prime_combination(vector<int>& nums, vector<bool>& visited, vector<int>& v, int node, int n){
    if(v.size()==3){
        int num = v[0] + v[1] + v[2];
        if(primes[num]==1) return 1;
        else return 0;
    }
    
    int ret = 0;
    for(int i=node; i<n; i++){
        if(visited[i]==true) continue;
        visited[i] = true;
        v.push_back(nums[i]);
        ret += get_prime_combination(nums, visited, v, i+1, n);
        visited[i] = false;
        v.pop_back();
    }
    return ret;
}

int solution(vector<int> nums) {
    int answer = -1;
    // init
    int n = nums.size();
    for(int i=2; i<=1500; i++){
        if(primes[i]==0) continue;
        for(int j=i+i; j<=3000; j+=i)
            primes[j] = 0;
    }
    vector<bool> visited(n, false);
    vector<int> v;
    answer = get_prime_combination(nums, visited, v, 0, n);
    
    return answer;
}