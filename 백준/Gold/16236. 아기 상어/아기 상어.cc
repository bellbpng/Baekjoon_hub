#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

int N;
int board[20][20];
int visited[20][20] = { false, };
int dist[20][20]; // 아기 상어가 접근할 수 있는 물고기와의 거리 정보
int minDist = 1000, minX = 20, minY = 20;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void init() {
	memset(visited, false, sizeof(visited));
	memset(dist, 0, sizeof(dist));
	minDist = 1000, minX = 20, minY = 20;
}

void Bfs(pair<int, int> babyShark, int size) {
	queue<pair<int, int>> q;
	q.push(babyShark);
	visited[babyShark.first][babyShark.second] = true;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
			if (board[nextX][nextY] > size) continue;
			if (visited[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			q.push(make_pair(nextX, nextY));
			dist[nextX][nextY] = dist[cpos.first][cpos.second] + 1;

			// 먹을 수 있는 물고기
			if (board[nextX][nextY] > 0 && board[nextX][nextY] < size) {
				if (dist[nextX][nextY] < minDist) {
					minDist = dist[nextX][nextY];
					minX = nextX, minY = nextY;
				}
				else if (dist[nextX][nextY] == minDist) {
					if (nextX < minX) { // 더 위쪽에 있는 경우
						minX = nextX, minY = nextY;
					}
					else if (nextX == minX) {
						if (nextY < minY) // 더 왼쪽에 있는 경우
							minX = nextX, minY = nextY;
					}
				}
			}
		}
	}
}


int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	scanf("%d", &N);
	pair<int, int> babyShark;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			scanf("%d", &board[r][c]);
			if (board[r][c] == 9) 
				babyShark = { r,c };
		}
	}

	int ans = 0;
	int size = 2;
	int eatCnt = 0;
	while (true) {
		init();

		Bfs(babyShark, size);
		if (minDist == 1000) break;
		ans += minDist;
		eatCnt++;
		if (eatCnt == size) {
			eatCnt = 0;
			size++;
		}
		board[babyShark.first][babyShark.second] = 0;
		board[minX][minY] = 0;
		babyShark = { minX, minY };
		board[babyShark.first][babyShark.second] = 9;
	}

	printf("%d\n", ans);
	return 0;
}