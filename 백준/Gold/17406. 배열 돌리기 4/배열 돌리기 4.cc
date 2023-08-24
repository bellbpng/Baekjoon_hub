#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

typedef struct _rot {
	int r, c, s;
} Rotate;

int N, M, K;
vector<Rotate> rotList;
vector<int> candRot;
int board[51][51];
int nboard[51][51];
int cboard[51][51];
bool rotated[51][51];
bool visited[6];
int minSum = 9e8;

void printBoard() {
	printf("-----------------------\n");
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			printf("%d ", board[r][c]);
		}
		printf("\n");
	}
}


void rotateArray(int x, int y, int s) {
	if (rotated[x][y]) {
		nboard[x - 1][y - 1] = board[x - 1][y - 1]; // 가운데 부분
		memcpy(board, nboard, sizeof(nboard));
		return;
	}

	int xLimit = x + 2 * s;
	int yLimit = y + 2 * s;

	// 가로줄
	for (int c = y; c <= yLimit; c++) {
		rotated[x][c] = true;
		rotated[xLimit][c] = true;
		if (c == y) {
			nboard[x][c] = board[x + 1][c];
			nboard[xLimit][c] = board[xLimit][c + 1];
		}
		else if(c==yLimit){
			nboard[x][c] = board[x][c - 1];
			nboard[xLimit][c] = board[xLimit - 1][c];
		}
		else {
			nboard[x][c] = board[x][c - 1];
			nboard[xLimit][c] = board[xLimit][c + 1];
		}
	}
	// printBoard();

	// 세로줄
	for (int r = x + 1; r < xLimit; r++) {
		rotated[r][y] = true;
		rotated[r][yLimit] = true;
		nboard[r][y] = board[r + 1][y];
		nboard[r][yLimit] = board[r - 1][yLimit];
	}
	// printBoard();
	rotateArray(x + 1, y + 1, s - 1);
}

void getRowSum() {
	int sum = 0;
	int aSum = 9e8;
	for (int r = 1; r <= N; r++) {
		sum = 0;
		for (int c = 1; c <= M; c++) {
			sum += board[r][c];
		}
		aSum = min(aSum, sum);
	}

	minSum = min(minSum, aSum);
}

void setRotationCand(int v) {
	if (candRot.size() == K) {
		memcpy(board, cboard, sizeof(cboard));
		
		// 회전 로직
		for (auto ele : candRot) {
			memset(rotated, false, sizeof(rotated));
			memcpy(nboard, board, sizeof(board));
			int startX = rotList[ele].r - rotList[ele].s;
			int startY = rotList[ele].c - rotList[ele].s;
			rotateArray(startX, startY, rotList[ele].s);
			// printBoard();
		}
		// printBoard();

		// 회전이 끝난 배열의 값 계산
		getRowSum();
		return;
	}

	for (int i = 0; i < K; i++) {
		if (visited[i]) continue;
		visited[i] = true;
		candRot.push_back(i);
		setRotationCand(i + 1);
		candRot.pop_back();
		visited[i] = false;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(board, 0, sizeof(board));
	scanf("%d %d %d", &N, &M, &K);
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			scanf("%d", &board[r][c]);
			cboard[r][c] = board[r][c];
		}
	}

	Rotate rot;
	for (int i = 0; i < K; i++) {
		scanf("%d %d %d", &rot.r, &rot.c, &rot.s);
		rotList.push_back(rot);
	}

	memset(visited, false, sizeof(visited));
	setRotationCand(0);
	printf("%d\n", minSum);
	return 0;
}