#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;
int N, ans = 0;
stack<int> basket;

void grabAndPut(vector<vector<int>>& board, int idx){
    for(int r=0; r<N; r++){
        if(board[r][idx]!=0){
            if(basket.size()>0){
                if(basket.top()==board[r][idx]){
                    basket.pop();
                    board[r][idx]=0;
                    ans+=2;
                    break;
                }
            }
            basket.push(board[r][idx]);
            board[r][idx]=0;
            break;
        }
    }
}

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    N = board.size();
    for(int i=0; i<moves.size(); i++){
        grabAndPut(board, moves[i]-1);
    }
    answer = ans;
    
    return answer;
}