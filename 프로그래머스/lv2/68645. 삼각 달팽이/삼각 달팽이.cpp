#include <string>
#include <vector>
#include <memory.h>
#include <iostream>
using namespace std;

vector<int> solution(int n) {
    int board[1000][1000];
    int visited[1000][1000];
    // 남쪽, 동쪽, 북서쪽 방향
    // 반드시 이 순서대로 진행해야함
    int dx[3] = {1, 0, -1}; 
    int dy[3] = {0, 1, -1};
    
    vector<int> answer;
    
    // 전체 칸의 개수
    int len = 0;
    for(int i=1; i<=n; i++){
        len += i;
    }
    
    memset(board, 0, sizeof(board));
    memset(visited, false, sizeof(visited));
    int sx = 0, sy = 0, dir = 0;
    board[sx][sy]=1;
    visited[sx][sy]=true;
    
    for(int i=2; i<=len; i++){
        int nextX = sx + dx[dir];
        int nextY = sy + dy[dir];
        if(nextX<0 || nextX>=n || nextY<0 || nextY>=n){
            dir = (dir+1)%3;
        }
        else if(visited[nextX][nextY]){
            dir = (dir+1)%3;
        }
        nextX = sx + dx[dir];
        nextY = sy + dy[dir];
        board[nextX][nextY] = i;
        visited[nextX][nextY]=true;
        sx = nextX, sy = nextY;
    }
    
    for(int r=0; r<n; r++){
        for(int c=0; c<n; c++){
            if(board[r][c]!=0){
                answer.push_back(board[r][c]);
            }
        }
    }
    
    return answer;
}