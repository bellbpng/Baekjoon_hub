#include <string>
#include <vector>
#include <queue>
using namespace std;

bool CheckHistory(vector<vector<int>>& history, int hidx){
    pair<int, int> cfrom = {history[hidx][0], history[hidx][1]};
    pair<int, int> cto = {history[hidx][2], history[hidx][3]};
    pair<int, int> bfrom, bto;
    for(int i=0; i<hidx; i++){
        bfrom = {history[i][0], history[i][1]};
        bto = {history[i][2], history[i][3]};
        if(cfrom==bfrom && cto==bto) return false;
        else if(cfrom==bto && cto==bfrom) return false;
    }
    return true;
}

bool CheckArea(int x, int y){
    if(x>=-5 && x<=5 && y>=-5 && y<=5)
        return true;
    else
        return false;
}

int solution(string dirs) {
    int answer = 1; // 원점에서 출발할 때는 항상 처음 걸어본 길
    vector<vector<int>> history(500, vector<int>(4, 0));
    
    int cx=0, cy=0, nx, ny, hidx=0;
    for(int i=0; i<dirs.size(); i++){
        if(dirs[i]=='U'){
            nx = cx, ny = cy+1;
        }
        else if(dirs[i]=='D'){
            nx = cx, ny = cy-1;
        }
        else if(dirs[i]=='R'){
            nx = cx+1, ny = cy;
        }
        else if(dirs[i]=='L'){
            nx = cx-1, ny = cy;
        }
        if(CheckArea(nx, ny)==false) continue;
        history[hidx++] = {cx, cy, nx, ny};  
        cx=nx, cy=ny;
        if(hidx==1) continue;
        if(CheckHistory(history, hidx-1)) answer++;
    }
    
    return answer;
}