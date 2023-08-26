#include <iostream>
#include <vector>
using namespace std;

typedef struct _ball {
	int mass, speed, dir;
} Fireball;

int N, M, K;
// 0 ~ 7 이동 방향
int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
vector<Fireball> ballTable[51][51];

void printBall() {
	printf("--------------------\n");
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			printf("[%d, %d] Fireball (Mass, Speed, Dir): ", r, c);
			for (int i = 0; i < ballTable[r][c].size(); i++) {
				printf("(%d, %d, %d)", ballTable[r][c][i].mass, ballTable[r][c][i].speed, ballTable[r][c][i].dir);
			}
			printf("\n");
		}
	}
}

int afterMove() {
	vector<Fireball> nballTable[51][51];
	int ret = 0;

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			// 같은 칸에 파이어볼은 모두 하나로 합쳐진다.
			int sumMass = 0, sumSpeed = 0, count = 0;
			bool odd = true, even = true;
			for (int i = 0; i < ballTable[r][c].size(); i++) {
				sumMass += ballTable[r][c][i].mass;
				sumSpeed += ballTable[r][c][i].speed;
				count++;
				if (ballTable[r][c][i].dir % 2 == 0) odd = false;
				else even = false;
			}
			if (count >= 2) {
				int nmass = sumMass / 5;
				int nspeed = sumSpeed / count;
				Fireball nball[4];
				if (nmass == 0) { // 질량이 0인 파이어볼은 소멸
					ballTable[r][c].clear();
					continue;
				}
				if (odd || even) { // 방향이 모두 홀수 혹은 짝수인 경우
					nball[0] = { nmass, nspeed, 0 };
					nball[1] = { nmass, nspeed, 2 };
					nball[2] = { nmass, nspeed, 4 };
					nball[3] = { nmass, nspeed, 6 };
				}
				else {
					nball[0] = { nmass, nspeed, 1 };
					nball[1] = { nmass, nspeed, 3 };
					nball[2] = { nmass, nspeed, 5 };
					nball[3] = { nmass, nspeed, 7 };
				}
				for (int k = 0; k < 4; k++)
					nballTable[r][c].push_back(nball[k]);
			}
			else if(count==1) {
				nballTable[r][c].push_back(ballTable[r][c][0]);
			}
			ballTable[r][c].clear();
		}
	}

	// update ballTable
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			for (auto ele : nballTable[r][c]) {
				ret += ele.mass;
				ballTable[r][c].push_back(ele);
			}
		}
	}

	return ret;
}

void moveFireball() {
	vector<Fireball> nballTable[51][51];

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			for (int i = 0; i < ballTable[r][c].size(); i++) {
				int nextX = r;
				int nextY = c;
				Fireball ball = ballTable[r][c][i];
				for (int s = 0; s < ball.speed; s++) {
					nextX += dx[ball.dir];
					nextY += dy[ball.dir];
					if (nextX < 1) nextX = N;
					else if (nextX > N) nextX = 1;
					if (nextY < 1) nextY = N;
					else if (nextY > N) nextY = 1;
				}
				nballTable[nextX][nextY].push_back(ball);
			}
			ballTable[r][c].clear();
		}
	}

	// update ballTable
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			for (auto ele : nballTable[r][c]) {
				ballTable[r][c].push_back(ele);
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d %d", &N, &M, &K);
	int x, y, m, s, d;
	Fireball ball;

	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d %d", &x, &y, &m, &s, &d);
		ball = { m,s,d };
		ballTable[x][y].push_back(ball);
	}

	int ans = 0;
	for (int i = 0; i < K; i++) {
		moveFireball();
		// printBall();
		ans = afterMove();
		if (ans == 0) break;
	}
	printf("%d\n", ans);
	return 0;
}