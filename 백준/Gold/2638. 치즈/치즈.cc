#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

int N, M;
// -1: 치즈를 녹게하는 공기, 0: 치즈를 녹이지 못하는 공기
// 1: 녹지 않는 치즈, 2: 녹는 치즈
int board[100][100];
int cheeseCnt = 0;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

// 치즈를 녹게하는 공기 결정
void setCritialAir() {
	bool visited[100][100];
	memset(visited, false, sizeof(visited));
	queue<pair<int, int>> q;
	q.push(make_pair(0, 0)); // 항상 노출된 공기 영역
	visited[0][0] = true;
	board[0][0] = -1;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
			if (board[nextX][nextY] == 1) continue;
			if (visited[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			q.push(make_pair(nextX, nextY));
			board[nextX][nextY] = -1;
		}
	}
}

void spendHour() {
	// 공기 셋팅
	setCritialAir();
	// printBoard();

	// 치즈 녹이기
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (board[r][c] == 1) {
				int cnt = 0;
				for (int dir = 0; dir < 4; dir++) {
					int nextX = r + dx[dir];
					int nextY = c + dy[dir];
					if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
					if (board[nextX][nextY] == -1) cnt++;
				}
				if (cnt >= 2) {
					cheeseCnt--;
					board[r][c] = 0;
				}
			}
		}
	}
	// printBoard();

	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (board[r][c] == -1) board[r][c] = 0;
		}
	}
	// printBoard();
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d", &N, &M);
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			scanf("%d", &board[r][c]);
			if (board[r][c] == 1) cheeseCnt++;
		}
	}

	int ans = 0;
	while (true) {
		if (cheeseCnt <= 0) break;
		spendHour();
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}