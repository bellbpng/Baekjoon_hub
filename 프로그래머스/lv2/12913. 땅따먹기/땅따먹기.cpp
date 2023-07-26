#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int> > land)
{
    int answer = 0;
    int n = land.size();
    // init
    vector<vector<int>> dp(n, vector<int>(4, 0));
    for(int i=0; i<4; i++)
        dp[0][i] = land[0][i];
    
    int val = 0;
    for(int r=1; r<n; r++){
        for(int c=0; c<4; c++){
            for(int k=0; k<4; k++){
                if(c==k) continue;
                dp[r][c] = max(dp[r][c], dp[r-1][k] + land[r][c]);
            }
        }
    }
    
    for(int i=0; i<4; i++){
        answer = answer < dp[n-1][i] ? dp[n-1][i] : answer;
    }
    
    return answer;
}