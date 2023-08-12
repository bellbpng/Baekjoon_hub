#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

int R, C, T;
int room[51][51] = { 0, };
int nRoom[51][51];
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
vector<int> airX;

// 1. 모든 미세먼지들의 확산 로직
void DustDiffustion(int xpos, int ypos) {
	int cnt = 0;
	int diffuseDust;
	for (int dir = 0; dir < 4; dir++) {
		int nextX = xpos + dx[dir];
		int nextY = ypos + dy[dir];
		if (nextX<1 || nextX>R || nextY<1 || nextY>C) continue;
		if (room[nextX][nextY] == -1) continue;
		diffuseDust = room[xpos][ypos] / 5;
		nRoom[nextX][nextY] += diffuseDust;
		cnt++;
	}

	nRoom[xpos][ypos] -= (diffuseDust * cnt);
}

// 2. 공기청정기 로직
void CleanAir() {
	for (int r = 1; r <= R; r++) {
		if (r == 1 || r == R) { // 왼쪽 방향
			for (int c = C-1; c >= 1; c--) {
				nRoom[r][c] = room[r][c + 1];
			}
			if (r == 1) nRoom[r][C] = room[r + 1][C];
			else if (r == R) nRoom[r][C] = room[r - 1][C];
		}
		else if (r == airX[0] || r==airX[1]) { // 오른쪽 방향
			for (int c = 2; c <= C; c++) {
				if (c == 2) nRoom[r][c] = 0;
				else nRoom[r][c] = room[r][c - 1];
			}
		}
		else if (r<airX[0]) { // 공기청정기 위쪽 지역
			nRoom[r][1] = room[r - 1][1];
			nRoom[r][C] = room[r+1][C];
		}
		else if (r > airX[1]) { // 공기청정기 아래쪽 지역
			nRoom[r][1] = room[r + 1][1];
			nRoom[r][C] = room[r - 1][C];
		}
	}
	memcpy(room, nRoom, sizeof(nRoom));
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d %d", &R, &C, &T);
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			scanf("%d", &room[r][c]);
			if (room[r][c] == -1) airX.push_back(r);
		}
	}

	for (int t = 0; t < T; t++) {
		// 1. 미세먼지 확산
		memcpy(nRoom, room, sizeof(room));
		for (int r = 1; r <= R; r++) {
			for (int c = 1; c <= C; c++) {
				if (room[r][c] > 0) DustDiffustion(r, c);
			}
		}
		memcpy(room, nRoom, sizeof(room));

		// 2. 공기청정기
		CleanAir();
	}
	
	// 미세먼지양 계산
	int ans = 0;
	for (int r = 1; r <= R; r++) {
		for (int c = 1; c <= C; c++) {
			if (room[r][c] > 0) ans += room[r][c];
		}
	}
	printf("%d\n", ans);
	return 0;
}