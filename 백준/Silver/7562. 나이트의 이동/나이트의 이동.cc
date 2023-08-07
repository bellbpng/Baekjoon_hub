#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int knightMove[8][2] = { {-1, -2}, {-2,-1}, {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2} };


typedef struct _posInfo {
	int x;
	int y;
} Pos;

void Bfs(int curX, int curY, int targetX, int targetY, int l) {
	vector<vector<int>> board(l, vector<int>(l, 100000));
	queue<Pos> q;
	board[curX][curY] = 0;
	q.push({ curX, curY });

	while (!q.empty()) {
		Pos cpos = q.front();
		q.pop();
		for (int dir = 0; dir < 8; dir++) {
			int nextX = cpos.x + knightMove[dir][0];
			int nextY = cpos.y + knightMove[dir][1];
			if (nextX >= 0 && nextX < l && nextY >= 0 && nextY < l) {
				if (board[nextX][nextY] > board[cpos.x][cpos.y]+1) {
					board[nextX][nextY] = board[cpos.x][cpos.y] + 1;
					q.push({ nextX, nextY });
				}
			}
		}
	}
	printf("%d\n", board[targetX][targetY]);
}


int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	scanf("%d", &T);

	for (int testCase = 0; testCase < T; testCase++) {
		int l, curX, curY, targetX, targetY;
		scanf("%d %d %d %d %d", &l, &curX, &curY, &targetX, &targetY);
		Bfs(curX, curY, targetX, targetY, l);
	}
	return 0;
}