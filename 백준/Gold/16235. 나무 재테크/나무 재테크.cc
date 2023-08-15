#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
using namespace std;

int N, M, K;
int A[11][11] = { 0, };
int land[11][11];
int lenTable[11][11];
int ans = 0; // 살아 있는 나무의 개수
int dx[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
int dy[8] = { 0, 0, -1, 1, 1, -1, 1, -1 };
vector<int> treeTable[101][101]; // treeTable[x][y][i] 는 x,y에 위치한 i번째 tree

void springSummer() {
	int nland[11][11]; // 죽은 나무들의 양분이 더해진 땅의 상태
	memcpy(nland, land, sizeof(land));
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			// 나이 순서대로 오름차순 정렬
			vector<int> tmp;
			sort(treeTable[r][c].begin(), treeTable[r][c].end());
			int len = lenTable[r][c];
			for (int i = 0; i < len; i++) {
				if (land[r][c] >= treeTable[r][c][i]) {
					land[r][c] -= treeTable[r][c][i];
					nland[r][c] -= treeTable[r][c][i];
					tmp.push_back(treeTable[r][c][i]+1);
				}
				else {
					ans--;
					nland[r][c] += (treeTable[r][c][i] / 2); // 죽은 나무의 양분
				}
			}
			treeTable[r][c].clear();
			for (auto ele : tmp) {
				treeTable[r][c].push_back(ele);
			}
			lenTable[r][c] = treeTable[r][c].size();
		}
	}
	memcpy(land, nland, sizeof(nland));
}

void fall() {
	int nlenTable[11][11];
	memcpy(nlenTable, lenTable, sizeof(lenTable));
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			int len = lenTable[r][c];
			for (int i = 0; i < len; i++) {
				if (treeTable[r][c][i] % 5 != 0) continue;
				for (int dir = 0; dir < 8; dir++) {
					int nextX = r + dx[dir];
					int nextY = c + dy[dir];
					if (nextX<1 || nextX>N || nextY<1 || nextY>N) continue;
					treeTable[nextX][nextY].push_back(1);
					nlenTable[nextX][nextY]++;
					ans++;
				}
			}
		}
	}
	memcpy(lenTable, nlenTable, sizeof(nlenTable));
}

void winter() {
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			land[r][c] += A[r][c];
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	scanf("%d %d %d", &N, &M, &K);
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			scanf("%d", &A[r][c]);
			land[r][c] = 5;
		}
	}
	
	memset(lenTable, 0, sizeof(lenTable));
	int x, y, age;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &x, &y, &age);
		treeTable[x][y].push_back(age);
		lenTable[x][y]++;
		ans++;
	}
	
	for (int i = 0; i < K; i++) {
		springSummer();
		fall();
		winter();
	}
	printf("%d\n", ans);
	return 0;
}