#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    int n = prices.size();
    vector<int> answer(n,-1);
    stack<int> stk;
    stk.push(0);
    for(int i=1; i<n; i++){
        while(!stk.empty()){
            if(prices[stk.top()] > prices[i]){
                answer[stk.top()] = i - stk.top();
                stk.pop();
            }
            else
                break;
        }
        stk.push(i);
    }
    
    while(!stk.empty()){
        answer[stk.top()] = n-1-stk.top();
        stk.pop();
    }
    
    return answer;
}