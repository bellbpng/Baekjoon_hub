#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;

int N, M;
int northOcean[300][300] = { 0, };
int ice[300][300] = { 0, };; // 빙산인 곳은 1, 바다는 0
bool visited[300][300] = { false, };
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int Bfs(int xpos, int ypos) {
	queue<pair<int, int>> q;
	vector<pair<int, int>> history;
	q.push(make_pair(xpos, ypos));
	visited[xpos][ypos] = true;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		history.push_back(cpos);
		q.pop();

		// 줄어들 높이 계산
		int cnt = 0;
		for (int dir = 0; dir < 4; dir++) {
			pair<int, int> sea;
			sea.first = cpos.first + dx[dir];
			sea.second = cpos.second + dy[dir];
			if (sea.first < 0 || sea.first >= N || sea.second < 0 || sea.second >= M) continue;
			if (ice[sea.first][sea.second] == 0) cnt++;
		}
		northOcean[cpos.first][cpos.second] -= cnt;

		// 다음에 방문할 좌표를 결정
		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
			if (ice[nextX][nextY] == 1) {
				if (visited[nextX][nextY]) continue;
				visited[nextX][nextY] = true;
				q.push(make_pair(nextX, nextY));
			}
		}
	}

	// 녹은 빙산들 중 높이가 0보다 작아 바다가 된 칸을 표시한다.
	for (auto pos : history) {
		if (northOcean[pos.first][pos.second] <= 0) {
			ice[pos.first][pos.second] = 0;
			northOcean[pos.first][pos.second] = 0;
		}
	}

	return 1;
}

int SpendYears() {
	// 빙산이 위치한 좌표를 찾는다.
	int cnt = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (northOcean[r][c] > 0 && visited[r][c]==false)
				cnt += Bfs(r, c);
		}
	}

	if (cnt > 1) return 0;
	if (cnt==1) return 1; // 한덩어리인 경우
	if (cnt == 0) return 2; // 전부다 녹은 경우
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d", &N, &M);
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			scanf("%d", &northOcean[r][c]);
			if (northOcean[r][c] > 0) ice[r][c] = 1;
		}
	}

	int ans = 0;
	int ret;
	while (true) {
		ret = SpendYears();
		if (ret == 0) break;
		else if (ret == 2) {
			ans = 0;
			break;
		}
		memset(visited, false, sizeof(visited));
		ans++;
	}
	 printf("%d\n", ans);
	return 0;
}