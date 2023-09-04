#include <string>
#include <vector>
#include <memory.h>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

vector<string> cboard;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool search(int sx, int sy){
    vector<pair<int, int>> cand;
    int dist[5][5];
    bool visited[5][5];
    memset(dist, 0, sizeof(dist));
    memset(visited, false, sizeof(dist));
    
    queue<pair<int, int>> q;
    q.push(make_pair(sx, sy));
    dist[sx][sy] = 0;
    visited[sx][sy] = true;
    
    while(!q.empty()){
        pair<int, int> cpos = q.front();
        q.pop();
        
        for(int dir=0; dir<4; dir++){
            int nx = cpos.first + dx[dir];
            int ny = cpos.second + dy[dir];
            if(nx<0 || nx>=5 || ny<0 || ny>=5) continue;
            if(visited[nx][ny]) continue;
            visited[nx][ny] = true;
            q.push(make_pair(nx, ny));
            dist[nx][ny] = dist[cpos.first][cpos.second]+1;
            if(cboard[nx][ny]=='P'){
                // 거리가 1인 경우는 바로 옆이므로 거리두기가 항상 지켜지지 않음
                if(dist[nx][ny]==1) return false;
                if(dist[nx][ny]==2) cand.push_back(make_pair(nx, ny));
            }
        }
    }

    // 두 점 사이에 테이블이 놓여 있는지 확인
    for(auto ele:cand){
        // 같은 행에 있는 경우
        if(sx==ele.first){
            int my = (sy + ele.second)/2;
            // printf("same raw: %d, %d\n", sx, my);
            if(cboard[sx][my]!='X') return false; 
        }
        // 같은 열에 있는 경우
        else if(sy==ele.second){
            int mx = (sx + ele.first)/2;
            // printf("same col: %d, %d\n", mx, sy);
            if(cboard[mx][sy]!='X') return false;
        }
        // 대각선에 있는 경우
        else {
            int x1 = sx;
            int y1 = ele.second;
            int x2 = ele.first;
            int y2 = sy;
            // printf("check two points, [%d, %d] and [%d, %d]\n", x1, y1, x2, y2);
            if(cboard[x1][y1]!='X' || cboard[x2][y2]!='X') return false;
        }
    }
    
    return true;
}

int checkSafeZone(){
    // 응시자가 앉은 자리를 찾은 후 거리 2까지 탐색
    for(int r=0; r<5; r++){
        for(int c=0; c<5; c++){
            if(cboard[r][c]=='P'){
                if(search(r,c)==false) return 0; 
            }
        }
    }
    return 1;
}


vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    
    for(int i=0; i<places.size(); i++){
        cboard.clear();
        for(int j=0; j<5; j++){
            cboard.push_back(places[i][j]);
        }
        answer.push_back(checkSafeZone());
    }
    
    
    return answer;
}