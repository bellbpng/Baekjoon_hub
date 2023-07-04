#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Debugging
void print_map(vector<vector<int>> map, int col, int row){
    for(int r=0; r<=row; r++){
        for(int c=0; c<=col; c++)
            cout << map[r][c] << " ";
        cout << endl;
    }
}

// initialize
void init_map(vector<vector<int>>& dp_map, vector<vector<int>>& puddles, int col, int row){
    // 웅덩이 세팅
    for(auto puddle:puddles){
        int r = puddle[1];
        int c = puddle[0];
        dp_map[r][c] = 0;
    }
    
    // 웅덩이가 테두리(row=1, col=1) 있으면 해당 지점은 최단경로로 사용될 수 없다.
    int val = 1;
    for(int r=1; r<=row; r++){
        if(dp_map[r][1]==0) val = 0;
        dp_map[r][1] = val;
    }
    
    val = 1;
    for(int c=1; c<=col; c++){
        if(dp_map[1][c]==0) val = 0;
        dp_map[1][c] = val;
    }
    
}

// m은 열, n은 행
int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    vector<vector<int>> dp_map(n+1, vector<int>(m+1,-1));
    
    init_map(dp_map, puddles, m, n);
    
    for(int r=2; r<=n; r++){
        for(int c=2; c<=m; c++){
            if(dp_map[r][c]==0) continue;
            dp_map[r][c] = dp_map[r-1][c] + dp_map[r][c-1];
            dp_map[r][c] %= 1000000007;
        }
    }
    
    answer = dp_map[n][m];
    return answer;
}