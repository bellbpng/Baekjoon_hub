#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory.h>
using namespace std;

vector<string> board;
bool visited[12][6];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int ans = 0;

void printBoard() {
	printf("----------------------\n");
	for (int r = 0; r < 12; r++) {
		cout << board[r] << endl;
	}
}

void popPuyo(int x, int y, bool& flag) {
	int cnt = 1;
	char curColor = board[x][y];
	vector<string> nboard = board;
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = true;
	nboard[x][y] = '.';


	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();
		
		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= 12 || nextY < 0 || nextY >= 6) continue;
			if (board[nextX][nextY] != curColor) continue;
			if (visited[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			q.push(make_pair(nextX, nextY));
			nboard[nextX][nextY] = '.';
			cnt++;
		}
	}

	if (cnt >= 4) {
		flag = true;
		board = nboard;
	}
}

void setGravity() {
	int idx = 11;
	for (int c = 0; c < 6; c++) {
		idx = 11;
		for (int r = 11; r >= 0; r--) {
			if (board[r][c] != '.') {
				if (r == idx) {
					idx--;
					continue;
				}
				board[idx--][c] = board[r][c];
				board[r][c] = '.';
			}
		}
	}
}

bool playPuyo() {
	bool flag = false;
	memset(visited, false, sizeof(visited));
	for (int r = 0; r < 12; r++) {
		for (int c = 0; c < 6; c++) {
			if (board[r][c] == '.') continue;
			if (visited[r][c]) continue;
			popPuyo(r, c, flag);
		}
	}
	// printBoard();
	if (flag == false) return false;
	
	ans++;
	setGravity();
	// printBoard();
	return true;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	string line;
	for (int i = 0; i < 12; i++) {
		cin >> line;
		board.push_back(line);
	}

	while (true) {
		if (playPuyo() == false) break;
	}
	printf("%d\n", ans);
	return 0;
}