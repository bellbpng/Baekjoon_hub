#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>
#include <cmath>

using namespace std;

int N, L, R;
vector<vector<int>> land(50, vector<int>(50, 0));
int unitedNation[50][50] = { 0, }; // 연합 구역을 나타냄. 같은 연합은 같은 숫자
bool visited[50][50] = { false, };
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int Bfs(pair<int, int> spos, int area) {
	queue<pair<int, int>> q;
	int sum = 0, cnt = 0;
	q.push(spos);
	visited[spos.first][spos.second] = true;
	unitedNation[spos.first][spos.second] = area;
	sum = land[spos.first][spos.second];
	cnt = 1;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();

		int diff;
		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= N) continue;
			diff = abs(land[cpos.first][cpos.second] - land[nextX][nextY]);
			if (diff<L || diff>R) continue;
			if (visited[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			unitedNation[nextX][nextY] = area;
			q.push(make_pair(nextX, nextY));
			sum += land[nextX][nextY];
			cnt++;
		}
	}

	return sum / cnt;
}

void MovePeople() {
	vector<int> nPeople;
	int area = 1;

	// Set Union
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			if (unitedNation[r][c] == 0) {
				nPeople.push_back(Bfs(make_pair(r, c), area++));
			}
		}
	}

	// update land
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			int unitedNum = unitedNation[r][c];
			land[r][c] = nPeople[unitedNum - 1];
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d %d", &N, &L, &R);
	
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			scanf("%d", &land[r][c]);
		}
	}

	int ans = 0;
	vector<vector<int>> cland = land;
	while (true) {
		memset(unitedNation, 0, sizeof(unitedNation));
		memset(visited, false, sizeof(visited));
		MovePeople();
		if (cland == land) break;
		ans++;
		cland = land;
	}

	printf("%d\n", ans);
	return 0;
}