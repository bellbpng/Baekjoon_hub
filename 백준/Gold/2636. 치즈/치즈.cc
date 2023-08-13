#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

int N, M;
// -1: 영향력 있는 공기, 0: 영향력 없는 공기, 1:녹지 않는 치즈, 2:녹는 치즈
int board[100][100]; 
bool visited[100][100];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int ans = 0;

void airBfs(int xpos, int ypos) {
	memset(visited, false, sizeof(visited));
	queue<pair<int, int>> q;
	q.push(make_pair(xpos, ypos));
	visited[xpos][ypos] = true;
	board[xpos][ypos] = -1;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= N || nextY<0 || nextY>=M) continue;
			if (board[nextX][nextY] != 0) continue;
			if (visited[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			board[nextX][nextY] = -1;
			q.push(make_pair(nextX, nextY));
		}
	}
}

void cheeseBfs(int xpos, int ypos) {
	memset(visited, false, sizeof(visited));
	queue<pair<int, int>> q;
	q.push(make_pair(xpos, ypos));
	visited[xpos][ypos] = true;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();

		// 녹는 치즈 설정 & 다음 탐색할 치즈 담기
		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
			if (board[nextX][nextY] == -1) board[cpos.first][cpos.second] = 2; // 녹는 치즈
			if (board[nextX][nextY] == 1) {
				if (visited[nextX][nextY]) continue;
				visited[nextX][nextY] = true;
				q.push(make_pair(nextX, nextY));
			}
		
		}
	}
}

void printBoard() {
	printf("############################\n");
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			printf("%d	", board[r][c]);
		}
		printf("\n");
	}
}

int getCheeseCount() {
	int cnt = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++)
			if (board[r][c] == 1) cnt++;
	}
	if (cnt != 0) ans = cnt;
	return cnt;
}

void meltCheese() {
	int time = 0;
	while (true) {
		if (getCheeseCount() == 0) break;
		airBfs(0, 0);
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (board[r][c] == 1) {
					cheeseBfs(r, c);
				}
			}
		}
		// melt cheese
		for (int r = 0; r < N; r++) {
			for (int c = 0; c < M; c++) {
				if (board[r][c] == 2) board[r][c] = 0;
				if (board[r][c] == -1) board[r][c] = 0; // reset air area
			}
		}
		time++;

		// printBoard();
	}
	printf("%d\n%d\n", time, ans);
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	scanf("%d %d", &N, &M);
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			scanf("%d", &board[r][c]);
		}
	}
	meltCheese();

}