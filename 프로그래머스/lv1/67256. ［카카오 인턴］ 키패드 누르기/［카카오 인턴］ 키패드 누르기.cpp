#include <string>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;

int keypad[4][3];
bool visited[4][3];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
vector<pair<int, int>> table;

void setDistance(pair<int, int> spos){
    memset(keypad, 0, sizeof(keypad));
    memset(visited, false, sizeof(visited));
    queue<pair<int, int>> q;
    q.push(spos);
    visited[spos.first][spos.second] = true;
    
    while(!q.empty()){
        pair<int, int> cpos = q.front();
        q.pop();
        
        for(int dir=0; dir<4; dir++){
            int nextX = cpos.first + dx[dir];
            int nextY = cpos.second + dy[dir];
            if(nextX<0 || nextX>=4 || nextY<0 || nextY>=3) continue;
            if(visited[nextX][nextY]) continue;
            visited[nextX][nextY]=true;
            q.push(make_pair(nextX, nextY));
            keypad[nextX][nextY] = keypad[cpos.first][cpos.second]+1;
        }
    }
}

char touchKeypad(int number, pair<int, int>& leftPos, pair<int, int>& rightPos, string hand){
    pair<int, int> target = table[number];
    if(number==2 || number==5 || number==8 || number==0){
        int distL, distR;
        // Get Distance from Left
        setDistance(leftPos);
        distL = keypad[target.first][target.second];
        // Get Distance from Right
        setDistance(rightPos);
        distR = keypad[target.first][target.second];
        
        if(distL < distR) {
            leftPos = target;
            return 'L';
        }
        else if(distR < distL) {
            rightPos = target;
            return 'R';
        }
        else{ // 거리가 같은 경우
            if(hand=="left"){
                leftPos = target;
                return 'L';
            }
            else if(hand=="right"){
                rightPos = target;
                return 'R';
            }
        }
    }
    else if(number == 1 || number == 4 || number == 7){
        leftPos = target;
        return 'L';
    }
    else{
        rightPos = target;
        return 'R';
    }
}

string solution(vector<int> numbers, string hand) {
    string answer = "";
    pair<int, int> cLeftPos = {3, 0}; // * 키패드
    pair<int, int> cRightPos = {3, 2}; // # 키패드
    
    // init table
    table.push_back(make_pair(3,1)); // 0 키패드 위치
    for(int r=0; r<3; r++){
        for(int c=0; c<3; c++){
            table.push_back(make_pair(r,c));
        }
    }
    for(int i=0; i<numbers.size(); i++){
        answer.push_back(touchKeypad(numbers[i], cLeftPos, cRightPos, hand));
    }
    
    return answer;
}