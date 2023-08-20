#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
#include <algorithm>

using namespace std;

int N, K, S, X, Y;
int board[201][201];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

bool cmp(int a, int b) {
	return a < b;
}

void printBoard() {
	printf("##########################\n");
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			printf("%d ", board[r][c]);
		}
		printf("\n");
	}
}

void spreadVirus() {
	int source[201][201]; // 번식을 시작한 지점
	int cand[201][201]; // 번식을 통해 추가되는 칸
	memset(source, 0, sizeof(source));
	memset(cand, 0, sizeof(cand));
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (board[r][c] == 0) continue;
			if (source[r][c] == 0) source[r][c] = board[r][c];
			else source[r][c] = min(source[r][c], board[r][c]);
			for (int dir = 0; dir < 4; dir++) {
				int nextX = r + dx[dir];
				int nextY = c + dy[dir];
				if (nextX<1 || nextX>N || nextY<1 || nextY>N) continue;
				if (cand[nextX][nextY] == 0) cand[nextX][nextY] = board[r][c];
				else cand[nextX][nextY] = min(cand[nextX][nextY], board[r][c]);
			}
		}
	}

	// update board
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (cand[r][c] == 0) {
				if (source[r][c] != 0) {
					board[r][c] = source[r][c];
				}
				continue;
			}
			if (source[r][c] != 0) board[r][c] = source[r][c];
			else {
				board[r][c] = cand[r][c];
			}
		}
	}
	// printBoard();
}

bool checkBoard() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			if (board[r][c] == 0) 
				return true;
		}
	}
	return false;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d", &N, &K);
	memset(board, 0, sizeof(board));
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++)
			scanf("%d", &board[r][c]);
	}
	scanf("%d %d %d", &S, &X, &Y);
	for (int time = 0; time < S; time++) {
		if (checkBoard() == false) break;
		spreadVirus();
	}
	printf("%d\n", board[X][Y]);
	return 0;
}