#include <iostream>
#include <algorithm>
#include <queue>
#include <memory.h>
using namespace std;

typedef struct _data {
	int xpos, ypos, likes, empty;
} Data;

int N;
int studentLikeInfo[401][4];
int board[21][21];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
vector<Data> cand;

bool cmp(Data d1, Data d2) {
	if (d1.likes != d2.likes) {
		return d1.likes > d2.likes;
	}
	else if (d1.empty != d2.empty) {
		return d1.empty > d2.empty;
	}
	else if (d1.xpos != d2.xpos) {
		return d1.xpos < d2.xpos;
	}
	else {
		return d1.ypos < d2.ypos;
	}
}

void setData(int num, int x, int y) {
	Data idata = { x, y, 0, 0 };
	for (int dir = 0; dir < 4; dir++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (nx<1 || nx>N || ny<1 || ny>N) continue;
		for (int i = 0; i < 4; i++) {
			if (studentLikeInfo[num][i] == board[nx][ny]) {
				idata.likes++;
			}
		}
		if (board[nx][ny] == 0) idata.empty++;
	}
	cand.push_back(idata);
}

int getScore(int x, int y) {
	int num = board[x][y];
	int cnt = 0;
	for (int dir = 0; dir < 4; dir++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (nx<1 || nx>N || ny<1 || ny>N) continue;
		for (int i = 0; i < 4; i++) {
			if (board[nx][ny] == studentLikeInfo[num][i]) cnt++;
		}
	}
	if (cnt == 0) return 0;
	else if (cnt == 1) return 1;
	else if (cnt == 2) return 10;
	else if (cnt == 3) return 100;
	else if (cnt == 4) return 1000;
}

void printBoard() {
	printf("-------------------------\n");
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			printf("%d ", board[r][c]);
		}
		printf("\n");
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	memset(board, 0, sizeof(board));
	scanf("%d", &N);
	int num, s1, s2, s3, s4;
	for (int i = 0; i < N*N; i++) {
		scanf("%d %d %d %d %d", &num, &s1, &s2, &s3, &s4);
		studentLikeInfo[num][0] = s1;
		studentLikeInfo[num][1] = s2;
		studentLikeInfo[num][2] = s3;
		studentLikeInfo[num][3] = s4;

		cand.clear();
		// find empty space
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= N; c++) {
				if (board[r][c] == 0) {
					setData(num, r, c);
				}
			}
		}
		sort(cand.begin(), cand.end(), cmp);
		board[cand[0].xpos][cand[0].ypos] = num;
	}
	// printBoard();

	// 만족도 조사
	int answer = 0;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			answer += getScore(r, c);
		}
	}
	printf("%d\n", answer);
	return 0;
}