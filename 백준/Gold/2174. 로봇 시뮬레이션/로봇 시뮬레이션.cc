#include <iostream>
#include <vector>
using namespace std;

typedef struct _robot {
	int x, y, dir;
} Robot;

int A, B, N, M;
int board[101][101] = { 0, }; // board[x][y] 는 (x,y)에 위치한 로봇의 번호
// 동(0), 북(1), 서(2) 남(3)
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };
vector<Robot> robotList(101); // robotList[idx] 는 idx 번 로봇의 좌표, 방향 정보

void cmdLeft(int robotNum, int cnt) {
	int realCnt = cnt % 4; // 0인 경우 방향 그대로
	for (int i = 0; i < realCnt; i++) {
		robotList[robotNum].dir = (robotList[robotNum].dir + 1) % 4;
	}
}

void cmdRight(int robotNum, int cnt) {
	int realCnt = cnt % 4;
	for (int i = 0; i < realCnt; i++) {
		robotList[robotNum].dir = robotList[robotNum].dir - 1;
		if (robotList[robotNum].dir == -1) robotList[robotNum].dir = 3;
	}
}

bool cmdFront(int robotNum, int cnt) {
	int curX = robotList[robotNum].x;
	int curY = robotList[robotNum].y;
	int dir = robotList[robotNum].dir;
	for (int i = 0; i < cnt; i++) {
		int nextX = curX + dx[dir];
		int nextY = curY + dy[dir];
		if (nextX < 1 || nextX > A || nextY < 1 || nextY > B) {
			printf("Robot %d crashes into the wall\n", robotNum);
			return false;
		}
		if (board[nextX][nextY] == 0) {
			board[nextX][nextY] = robotNum;
			board[curX][curY] = 0;
			curX = nextX;
			curY = nextY;
			robotList[robotNum].x = nextX;
			robotList[robotNum].y = nextY;
			continue;
		}
		int crashNum = board[nextX][nextY];
		printf("Robot %d crashes into robot %d\n", robotNum, crashNum);
		return false;
	}
	return true;
}

bool playCommand(int robotNum, char cmd, int cnt) {
	if (cmd == 'L') cmdLeft(robotNum, cnt);
	else if (cmd == 'R') cmdRight(robotNum, cnt);
	else if (cmd == 'F') {
		if (cmdFront(robotNum, cnt) == false) return false;
		else return true;
	}
	return true;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d %d %d", &A, &B, &N, &M);
	int x, y;
	char dir;
	Robot rbt;
	for (int i = 0; i < N; i++) {
		scanf("%d %d %c", &x, &y, &dir);
		rbt.x = x;
		rbt.y = y;
		if (dir == 'E') {
			rbt.dir = 0;
		}
		else if (dir == 'N') {
			rbt.dir = 1;
		}
		else if (dir == 'W') {
			rbt.dir = 2;
		}
		else if (dir == 'S') {
			rbt.dir = 3;
		}
		robotList[i + 1] = rbt;
		board[x][y] = i + 1;
	}

	int robotNum, cnt;
	char cmd;
	bool flag = true;
	for (int i = 0; i < M; i++) {
		scanf("%d %c %d", &robotNum, &cmd, &cnt);
		if (flag) flag = playCommand(robotNum, cmd, cnt);
	}
	if (flag) printf("OK\n");

	return 0;
}