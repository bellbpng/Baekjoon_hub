#include <iostream>
#include <vector>
using namespace std;

int w, h;
// 상, 하, 좌, 우, 대각선 우상, 좌상, 좌하, 우하
int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dy[8] = { 0, 0, -1, 1, 1, -1, -1, 1 };

void Dfs(vector<vector<int>>& board, vector<vector<bool>>& visited, int x, int y) {
	for (int dir = 0; dir < 8; dir++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (nx<0 || nx>=h || ny<0 || ny>=w) continue;
		if (board[nx][ny]==0 || visited[nx][ny] == true) continue;
		visited[nx][ny] = true;
		Dfs(board, visited, nx, ny);
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	while (!cin.eof()) {
		cin >> w >> h;
		if (w == 0 && h == 0) break;
		vector<vector<int>> board(h, vector<int>(w));
		vector<vector<bool>> visited(h, vector<bool>(w, false));
		for (int r = 0; r < h; r++) {
			for (int c = 0; c < w; c++)
				cin >> board[r][c];
		}

		int cnt = 0;
		// find start position
		for (int r = 0; r < h; r++) {
			for (int c = 0; c < w; c++) {
				if (board[r][c] == 1 && visited[r][c] == false) {
					visited[r][c] = true;
					cnt++;
					Dfs(board, visited, r, c);
				}
			}
		}
		cout << cnt << endl;
	}
}