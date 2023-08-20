#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
#include <queue>
using namespace std;

int N, M;
int land[10][10];
bool visited[10][10];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
vector<vector<int>> costs; // costs[0]: from, costs[1]: to, costs[2]: weight
int countIsland;

void printLand() {
	printf("--------------------------\n");
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			printf("%d ", land[r][c]);
		}
		printf("\n");
	}
}

void printGraph() {
	printf("############################\n");
	for (int i = 0; i < costs.size(); i++) {
		printf("from: %d, to: %d, weight: %d\n", costs[i][0], costs[i][1], costs[i][2]);
	}
}

// 섬 번호를 메기기 위한 BFS
void bfsIsland(int x, int y, int area) {
	queue<pair<int, int>> q;
	q.push(make_pair(x, y));
	visited[x][y] = true;
	land[x][y] = area;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nextX = cpos.first + dx[dir];
			int nextY = cpos.second + dy[dir];
			if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) continue;
			if (land[nextX][nextY] == 0) continue;
			if (visited[nextX][nextY]) continue;
			visited[nextX][nextY] = true;
			q.push(make_pair(nextX, nextY));
			land[nextX][nextY] = area;
		}
	}
}

// 섬의 번호를 메긴다.
void setIsland() {
	int area = 0;
	memset(visited, false, sizeof(visited));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (land[r][c] == -1) {
				bfsIsland(r, c, ++area);
			}
		}
	}
	countIsland = area;
	// printLand();
}

// 섬과 섬을 연결하는 최소 다리 길이를 파악하여 그래프 노드 만들기
void setBridge(int x, int y, int dir, vector<bool>& linked) {
	int myNum = land[x][y];
	int curX = x, curY = y;
	int nextX, nextY, linkLand, dist = 0;
	while (true) {
		nextX = curX + dx[dir];
		nextY = curY + dy[dir];
		if (nextX < 0 || nextX >= N || nextY < 0 || nextY >= M) return;
		if (land[nextX][nextY] == myNum) return;
		dist++;
		if (land[nextX][nextY] != 0) { // 다른 섬을 만난 경우
			if (dist - 1 < 2) return;
			linkLand = land[nextX][nextY];
			linked[linkLand] = true;
			break;
		}
		curX = nextX;
		curY = nextY;
	}

	vector<int> ret(3);
	ret[0] = myNum;
	ret[1] = linkLand;
	ret[2] = dist-1;
	costs.push_back(ret);
	// printf("%d %d %d\n", ret[0], ret[1], ret[2]);
}

bool cmp(vector<int> v1, vector<int> v2) {
	return v1[2] < v2[2];
}

bool makeGraphNode() {
	vector<bool> linked(7, false);
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			if (land[r][c] != 0) {
				for (int dir = 0; dir < 4; dir++) {
					setBridge(r, c, dir, linked);
				}
			}
		}
	}

	// 연결이 불가능한 섬이 있는지 확인
	for (int num = 1; num <= countIsland; num++) {
		if (linked[num] == false) return false;
	}

	// 비용이 적은 것부터 오름차순 정렬
	sort(costs.begin(), costs.end(), cmp);
	// printGraph();
	return true;
}

int getGroup(vector<int> group, int n) {
	if (group[n] == n) return n;
	else return getGroup(group, group[n]);
}

void printGroup(vector<int>& group) {
	for (int i = 1; i <= countIsland; i++) {
		printf("Island %d in group %d\n", i, getGroup(group, i));
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int ans = 0;

	scanf("%d %d", &N, &M);
	memset(land, 0, sizeof(land));
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			scanf("%d", &land[r][c]);
			if (land[r][c] == 1) land[r][c] = -1; // 땅인 부분은 -1로 표현
		}
	}

	setIsland();
	if (makeGraphNode() == false) {
		printf("-1\n");
		return 0;
	}
	
	// 최소신장트리(MST) 만들기
	vector<int> group(countIsland + 1, 0);
	for (int num = 1; num <= countIsland; num++) {
		group[num] = num;
	}
	int from, to, w;
	int groupA, groupB;
	for (int i = 0; i < costs.size(); i++) {
		from = costs[i][0];
		to = costs[i][1];
		w = costs[i][2];
		groupA = getGroup(group, from);
		groupB = getGroup(group, to);
		if (groupA == groupB) continue;
		ans += w;
		if (groupA < groupB) {
			group[groupB] = groupA;
		}
		else {
			group[groupA] = groupB;
		}
	}
	// printGroup(group);

	// 그래프가 하나에 속하지 않는 경우
	int ref = getGroup(group, 1);
	for (int i = 2; i <= countIsland; i++) {
		if (ref != getGroup(group, i)) {
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n", ans);
}

