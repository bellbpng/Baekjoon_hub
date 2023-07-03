#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int n = triangle.size();
    
    vector<vector<int>> dp(n, vector<int>(n,0));
    dp[0][0] = triangle[0][0];
    
    for(int height=1; height<n; height++){
        for(int idx=0; idx<triangle[height].size(); idx++){
            if(idx==0) // 왼쪽 끝에 위치한 경우
                dp[height][idx] = dp[height-1][idx];
            else if(idx==triangle[height].size()-1) // 오른쪽 끝에 위치한 경우
                dp[height][idx] = dp[height-1][idx-1];
            else // 중간에 위치한 경우
                dp[height][idx] = max(dp[height-1][idx], dp[height-1][idx-1]);
            dp[height][idx] += triangle[height][idx];
            
            // Debugging
            // cout << dp[height][idx] << " ";
        }
    }
    
    
    answer = dp[n-1][0];
    for(int i=1; i<triangle[n-1].size(); i++){
        answer = answer < dp[n-1][i] ? dp[n-1][i] : answer;
    }
    
    return answer;
}