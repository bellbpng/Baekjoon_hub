#include <iostream>
#include <vector>
#include <string>
#include <memory.h>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct _pos {
	int xpos, ypos;
	char ch;
} Pos;

int N, M, ans = 0;
bool visited[20][20];
vector<string> board;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

void dfs(int x, int y, vector<int> history, char ch, int dist) {
	ans = max(ans, dist);
	for (int dir = 0; dir < 4; dir++) {
		int nx = x + dx[dir];
		int ny = y + dy[dir];
		if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
		if (history[board[nx][ny]-'A']==1) continue;
		history[board[nx][ny] - 'A'] = 1;
		dfs(nx, ny, history, board[nx][ny], dist + 1);
		history[board[nx][ny] - 'A'] = 0;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N >> M;
	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		board.push_back(str);
	}
	vector<int> history(26, 0);
	history[board[0][0] - 'A'] = 1;
	dfs(0, 0, history, board[0][0], 1);
	cout << ans << endl;
	return 0;
}