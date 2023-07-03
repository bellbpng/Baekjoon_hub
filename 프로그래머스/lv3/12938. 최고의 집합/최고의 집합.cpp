#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 제곱수를 최대한 많이 만드는 방법이 곱이 최대가 되는 방법이다.
vector<int> solution(int n, int s) {
    vector<int> answer;
    
    if(n>s) 
        answer.push_back(-1);
    else {
        for(int i=0; i<n; i++)
            answer.push_back(1);
        int diff = s - n;
        int val = diff/n;
        int margin = diff%n;
        for(int i=0; i<n; i++)
            answer[i] += val;
        for(int i=0; i<margin; i++)
            answer[n-1-i] += 1;
    }
    
    // Debugging
    // for(auto ele:answer)
        // cout << ele << " ";
    // cout << endl;
    
    return answer;
}