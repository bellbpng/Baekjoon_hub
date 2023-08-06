#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
using namespace std;

int n;
int board[100][100];
bool visited[100][100] = { false, };
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void Dfs(int x, int y, int h) {
	for (int dir = 0; dir < 4; dir++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (board[nx][ny] <= h || visited[nx][ny]) continue;
		visited[nx][ny] = true;
		Dfs(nx, ny, h);
	}
}

int main()
{
	cin >> n;
	int minH = 101, maxH = 0;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			cin >> board[r][c];
			if (minH > board[r][c]) minH = board[r][c];
			if (maxH < board[r][c]) maxH = board[r][c];
		}
	}

	if (minH == maxH) {
		cout << "1" << endl;
		return 0;
	}

	// find start position
	int ret = 0;
	for (int h = minH; h < maxH; h++) {
		int cnt = 0;
		memset(visited, false, sizeof(visited));
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				if (board[r][c] > h && !visited[r][c]) {
					visited[r][c] = true;
					cnt++;
					Dfs(r, c, h);
				}
			}
		}
		ret = max(ret, cnt);
	}
	cout << ret << endl;
	return 0;
}