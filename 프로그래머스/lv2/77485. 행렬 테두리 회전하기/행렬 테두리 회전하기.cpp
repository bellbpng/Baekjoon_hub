#include <string>
#include <vector>
#include <memory.h>
#include <iostream>
using namespace std;
int n, m;
int board[101][101];

void printBoard(int x1, int y1, int x2, int y2){
    for(int r=x1; r<=x2; r++){
        for(int c=y1; c<=y2; c++)
            printf("%d ", board[r][c]);
        printf("\n");
    }
}

int rotateBoard(int x1, int y1, int x2, int y2){
    int nboard[101][101];
    memcpy(nboard, board, sizeof(board));
    int minVal = 1e9;
    // 가로선
    for(int c=y1; c<=y2; c++){
        minVal = min(minVal, board[x1][c]);
        minVal = min(minVal, board[x2][c]);
        if(c==y1) {
            nboard[x1][c] = board[x1+1][c];
            nboard[x2][c] = board[x2][c+1];
        }
        else if(c==y2){
            nboard[x1][c] = board[x1][c-1];
            nboard[x2][c] = board[x2-1][c];
        }
        else{
            nboard[x1][c] = board[x1][c-1];
            nboard[x2][c] = board[x2][c+1];
        }
    }
    
    // 세로선 (중간 부분만)
    for(int r=x1+1; r<=x2-1; r++){
        minVal = min(minVal, board[r][y1]);
        minVal = min(minVal, board[r][y2]);
        nboard[r][y1] = board[r+1][y1];
        nboard[r][y2] = board[r-1][y2];
    }
    memcpy(board, nboard, sizeof(nboard));
    // cout << minVal << " ";
    return minVal;
}

vector<int> solution(int rows, int columns, vector<vector<int>> queries) {
    vector<int> answer;
    n = rows; m = columns;
    
    // init board
    int val = 1;
    for(int r=1; r<=n; r++){
        for(int c=1; c<=m; c++)
            board[r][c] = val++;
    }
    
    for(int i=0; i<queries.size(); i++){
        answer.push_back(rotateBoard(queries[i][0],queries[i][1],queries[i][2],queries[i][3]));
    }
    
    return answer;
}