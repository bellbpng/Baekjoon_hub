#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 첫번째 스티커를 뜯은 경우
int remove_first_sticker(vector<int>& sticker){
    int n = sticker.size();
    vector<int> dp(n,0);
    dp[0] = sticker[0];
    dp[1] = dp[0];
    
    // i번째 스티커를 뜯은 경우와 뜯지 않은 경우 중 큰 값을 선택
    for(int i=2; i<n; i++){
        dp[i] = max(sticker[i]+dp[i-2], dp[i-1]);
    }
    return dp[n-2]; // 첫번째를 뜯었기 때문에 n-2가 최대
}

// 첫번째 스티커를 뜯지 않은 경우
int not_remove_first_sticker(vector<int>& sticker){
    int n = sticker.size();
    vector<int> dp(n,0);
    dp[0] = 0;
    dp[1] = sticker[1];
    
    for(int i=2; i<n; i++){
        dp[i] = max(sticker[i]+dp[i-2], dp[i-1]);
    }
    return dp[n-1]; 
}

int solution(vector<int> sticker)
{
    int answer =0;
    
    if(sticker.size()==1) 
        answer = sticker[0];
    else
        answer = max(remove_first_sticker(sticker), not_remove_first_sticker(sticker));

    return answer;
}