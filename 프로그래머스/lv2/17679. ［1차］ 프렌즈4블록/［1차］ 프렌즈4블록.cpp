#include <string>
#include <vector>
#include <iostream>
#include <memory.h>
#include <queue>

using namespace std;

int movement[3][2] = {{0,1}, {1,0}, {1,1}};
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
vector<string> cboard;
bool visited[30][30];
int N, M;
int ans;

bool checkFourBlock(int x, int y){
    char ch = cboard[x][y];
    for(int i=0; i<3; i++){
        int nextX = x + movement[i][0];
        int nextY = y + movement[i][1];
        
        if(nextX<0 || nextX>=N || nextY<0 || nextY>=M) 
            return false;
        if(cboard[nextX][nextY] != ch)
            return false;
    }
    return true;
}

bool setRemoveBlock(){
   vector<vector<bool>> removed(30, vector<bool>(30, false));
    
    for(int r=0; r<N; r++){
        for(int c=0; c<M; c++){
            if(cboard[r][c]=='*') continue;
            if(checkFourBlock(r,c)){
                removed[r][c] = true;
                for(int i=0; i<3; i++){
                    int nextX = r + movement[i][0];
                    int nextY = c + movement[i][1];
                    removed[nextX][nextY] = true;
                }
            }
        }
    }
    
    // remove blocks
    int flag = 0;
    for(int r=0; r<N; r++){
        for(int c=0; c<M; c++){
            if(removed[r][c]){
                cboard[r][c] = '*';
                ans++;
                flag=1;
            }
        }
    }
    if(flag==0) return false;
    return true;
}

void moveDownBlocks(){
    char nboard[30][30];
    memset(nboard, 0, sizeof(nboard));
    
    for(int c=0; c<M; c++){
        int curR = N-1;
        for(int r=N-1; r>=0; r--){
            if(cboard[r][c]=='*') continue;
            nboard[curR--][c] = cboard[r][c];
        }
    }
    
    // 빈칸 채우기
    for(int r=0; r<N; r++){
        for(int c=0; c<M; c++){
            if(nboard[r][c]==0) 
                nboard[r][c]='*';
        }
    }
    
    for(int r=0; r<N; r++){
        cboard[r].clear();
        for(int c=0; c<M; c++){
            cboard[r].push_back(nboard[r][c]);
        }
    }
}

int solution(int m, int n, vector<string> board) {
    cboard = board;
    N = m, M = n;
    
    while(true){
        if(setRemoveBlock()==false)
            break;
        moveDownBlocks();
    }
    
    return ans;
}