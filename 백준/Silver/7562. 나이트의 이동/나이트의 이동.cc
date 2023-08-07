#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int knightMove[8][2] = {
	{-1, -2}, {-2,-1}, {-2,1}, {-1,2}, {1,2}, {2,1}, {2,-1}, {1,-2}
};

typedef struct _posInfo {
	int x;
	int y;
	int idx;
} Pos;

int Bfs(int curX, int curY, int targetX, int targetY, int l) {
	vector<vector<bool>> visited(l, vector<bool>(l, false));
	queue<Pos> q;
	q.push({ curX, curY, 0 });

	while (!q.empty()) {
		Pos cpos = q.front();
		visited[cpos.x][cpos.y] = true;
		q.pop();
		if (cpos.x == targetX && cpos.y == targetY) return cpos.idx;

		for (int dir = 0; dir < 8; dir++) {
			int nextX = cpos.x + knightMove[dir][0];
			int nextY = cpos.y + knightMove[dir][1];
			if (nextX < 0 || nextX >= l || nextY < 0 || nextY >= l) continue;
			if (visited[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			q.push({ nextX, nextY, cpos.idx + 1 });
		}
	}
}


int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	scanf("%d", &T);

	for (int testCase = 0; testCase < T; testCase++) {
		int l, ans=0;
		scanf("%d", &l);
		int curX, curY, targetX, targetY;
		scanf("%d %d", &curX, &curY);
		scanf("%d %d", &targetX, &targetY);
		ans = Bfs(curX, curY, targetX, targetY, l);
		printf("%d\n", ans);
	}
	return 0;
}