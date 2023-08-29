#include <string>
#include <vector>
#include <iostream>
using namespace std;

int N;
string ans;

void compress(vector<vector<int>>& arr, int sx, int sy, int step){
    bool flag = true;
    int ref = arr[sx][sy];
    for(int dx=0; dx<step; dx++){
        for(int dy=0; dy<step; dy++){
            int nextX = sx + dx;
            int nextY = sy + dy;
            if(arr[nextX][nextY]!=ref){
                flag = false;
                break;
            }
        }
    }
    
    if(flag) {
        ans.push_back('0'+ref);
        return;
    }
    
    int half = step/2;
    compress(arr, sx, sy, half);
    compress(arr, sx, sy+half, half);
    compress(arr, sx+half, sy, half);
    compress(arr, sx+half, sy+half, half);
}

vector<int> solution(vector<vector<int>> arr) {
    vector<int> answer(2,0);
    N = arr.size();
    
    compress(arr, 0, 0, N);
    for(int i=0; i<ans.length(); i++){
        answer[ans[i]-'0']++;
    }
    
    return answer;
}