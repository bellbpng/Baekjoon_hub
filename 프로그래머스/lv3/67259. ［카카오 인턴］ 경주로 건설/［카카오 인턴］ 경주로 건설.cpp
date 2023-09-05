#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

#define INF 9e8
using namespace std;

typedef struct _pos{
    int xpos;
    int ypos;
    int dir;
} Pos;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int N;
int cost[25][25][4];

void bfs(vector<vector<int>> board, int sx, int sy, int dir){
    queue<Pos> q;
    Pos cpos = {sx, sy, dir};
    q.push(cpos);
    
    while(!q.empty()){
        cpos = q.front();
        q.pop();
        
        for(int dir=0; dir<4; dir++){
            int nx = cpos.xpos + dx[dir];
            int ny = cpos.ypos + dy[dir];
            if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
            if(board[nx][ny]==1) continue;
            int ncst = 0;
            if(dir == cpos.dir) {
                ncst = cost[cpos.xpos][cpos.ypos][cpos.dir] + 100;
            }
            else{
                ncst = cost[cpos.xpos][cpos.ypos][cpos.dir] + 600;
            }
            if(cost[nx][ny][dir]==INF) {
                cost[nx][ny][dir] = ncst;
                q.push({nx, ny, dir});
            }
            else {
                if(ncst <= cost[nx][ny][dir]) {
                    cost[nx][ny][dir] = ncst;
                    q.push({nx, ny, dir});
                }
            }
        }
    }
    
}

int solution(vector<vector<int>> board) {
    int answer = INF;
    N = board.size();
    for(int r=0; r<N; r++){
        for(int c=0; c<N; c++){
            for(int dir=0; dir<4; dir++)
                cost[r][c][dir] = INF;
        }
    }
    for(int dir=0; dir<4; dir++)
        cost[0][0][dir]=0;
    
    bfs(board, 0, 0, 1); // 남쪽
    bfs(board, 0, 0, 3); // 동쪽
    
    for(int dir=0; dir<4; dir++)
        answer = min(answer, cost[N-1][N-1][dir]);
    return answer;
}