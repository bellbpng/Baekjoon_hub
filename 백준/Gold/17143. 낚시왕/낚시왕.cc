#include <iostream>
#include <vector>
#include <memory.h>
#include <algorithm>
using namespace std;

typedef struct _shark {
	int xpos, ypos, speed, size, dir;
	bool status;
} Shark; 
int R, C, M;
int ans = 0;
int board[101][101] = { 0, };
vector<Shark> sharkList;

// 땅에 가까운 순서대로 정렬
bool cmpRow(Shark s1, Shark s2) {
	return s1.xpos < s2.xpos;
}

void catchShark(int idx) {
	sort(sharkList.begin(), sharkList.end(), cmpRow);
	for (int i = 0; i < sharkList.size(); i++) {
		if (sharkList[i].status == false) continue;
		if (sharkList[i].ypos == idx) {
			ans += sharkList[i].size;
			sharkList[i].status = false;
			break;
		}
	}
}

void moveShark() {
	int vPeriod = (R - 1) * 2;
	int hPeriod = (C - 1) * 2;
	
	for (int i = 0; i < sharkList.size(); i++) {
		if (sharkList[i].status == false) continue;
		int dir = sharkList[i].dir;
		int remainSpeedV = sharkList[i].speed % vPeriod;
		int remainSpeedH = sharkList[i].speed % hPeriod;
		int xpos = sharkList[i].xpos;
		int ypos = sharkList[i].ypos;
		// printf("Before Move: %d %d\n", xpos, ypos);
		if (dir == 1 || dir == 2) {
			for (int i = 0; i < remainSpeedV; i++) {
				if (dir == 1) {
					xpos--;
					if (xpos == 0) {
						dir = 2;
						xpos = 2;
						continue;
					}
				}
				else if (dir == 2) {
					xpos++;
					if (xpos > R) {
						dir = 1;
						xpos = R - 1;
					}
				}
			}
		}
		else if (dir == 3 || dir == 4) {
			for (int i = 0; i < remainSpeedH; i++) {
				if (dir == 4) {
					ypos--;
					if (ypos == 0) {
						dir = 3;
						ypos = 2;
						continue;
					}
				}
				else if (dir == 3) {
					ypos++;
					if (ypos > C) {
						dir = 4;
						ypos = C - 1;
					}
				}
			}
		}
		// printf("After Move: %d %d\n", xpos, ypos);
		sharkList[i].xpos = xpos;
		sharkList[i].ypos = ypos;
		sharkList[i].dir = dir;
	}
}

// 크기가 큰 순서대로 정렬
bool cmpSize(Shark s1, Shark s2) {
	return s1.size > s2.size;
}

void setLiveShark() {
	memset(board, 0, sizeof(board));
	sort(sharkList.begin(), sharkList.end(), cmpSize);
	for (int i = 0; i < sharkList.size(); i++) {
		if (sharkList[i].status == false) continue;
		if (board[sharkList[i].xpos][sharkList[i].ypos] == 0)
			board[sharkList[i].xpos][sharkList[i].ypos] = 1;
		else if (board[sharkList[i].xpos][sharkList[i].ypos] == 1)
			sharkList[i].status = false;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d %d", &R, &C, &M);

	Shark s;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &s.xpos, &s.ypos, &s.speed, &s.dir, &s.size);
		s.status = true;
		sharkList.push_back(s);
	}
	
	for (int idx = 1; idx <= C; idx++) {
		catchShark(idx);
		moveShark();
		setLiveShark();
	}
	
	/*catchShark(1);
	moveShark();
	setLiveShark();
	int debug[5][7] = { 0, };
	for (auto shark : sharkList) {
		if (shark.status == false) continue;
		debug[shark.xpos][shark.ypos] = shark.size;
	}
	for (int r = 1; r <= 4; r++) {
		for (int c = 1; c <= 6; c++) {
			printf("%d ", debug[r][c]);
		}
		printf("\n");
	}*/

	printf("%d\n", ans);
	return 0;
}