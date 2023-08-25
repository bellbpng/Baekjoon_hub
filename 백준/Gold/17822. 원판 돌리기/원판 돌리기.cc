#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

typedef struct _rot {
	int x, d, k;
} Rot;

int N, M, T;
// x의 배수인 원판을 d방향으로 k칸 회전시킨다.
vector<Rot> rotInfo;
int table[51][51]; // 원판에 적힌 수는 시계 방향으로 자리함

void printTable() {
	printf("-----------------------\n");
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			printf("%d ", table[r][c]);
		}
		printf("\n");
	}
}

// r번 원판 위에 숫자가 모두 0인지 확인
bool checkValid(int r) {
	for (int c = 1; c <= M; c++) {
		if (table[r][c] != 0) return true;
	}
	return false;
}

void removeNumber() {
	bool removed[51][51];
	memset(removed, false, sizeof(removed));

	// 같은 원에 있는 경우
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c < M; c++) {
			if (table[r][c] == 0) continue;
			if (table[r][c] == table[r][c + 1]) {
				removed[r][c] = true;
				removed[r][c + 1] = true;
			}
		}
		if (table[r][1] == 0) continue;
		if (table[r][1] == table[r][M]) {
			removed[r][1] = true;
			removed[r][M] = true;
		}
	}
	
	// 같은 선에 있는 경우
	for (int c = 1; c <= M; c++) {
		for (int r = 1; r < N; r++) {
			if (table[r][c] == 0) continue;
			if (table[r][c] == table[r + 1][c]) {
				removed[r][c] = true;
				removed[r + 1][c] = true;
			}
		}
	}

	// 숫자 제거
	bool flag = false;
	int sum = 0;
	int cnt = 0;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			if (table[r][c] == 0) continue;
			if (removed[r][c]) {
				table[r][c] = 0;
				flag = true;
			}
			else {
				sum += table[r][c];
				cnt++;
			}
		}
	}

	// 지운 수가 없는 경우 평균 보다 작은 수는 +1, 큰 수는 -1
	float avg = (float)sum / cnt;
	if (flag == false) {
		for (int r = 1; r <= N; r++) {
			for (int c = 1; c <= M; c++) {
				if (table[r][c] == 0) continue;
				if (table[r][c] < avg) table[r][c]++;
				else if (table[r][c] > avg) table[r][c]--;
			}
		}
	}
	// printTable();
}

void rotateCircle(int x, int d, int k) {
	int ntable[51][51];
	memcpy(ntable, table, sizeof(table));
	// d=0 : 시계 방향, d=1: 반시계 방향
	// k칸 회전, 번호가 x의 배수인 원판
	if (d == 0) {
		for (int r = x; r <= N; r += x) {
			if (checkValid(r)==false) continue;
			for (int c = 1; c <= M; c++) {
				int nextC = c + k;
				if (nextC > M) nextC -= M;
				ntable[r][nextC] = table[r][c];
			}
		}
	}
	else if (d == 1) {
		for (int r = x; r <= N; r += x) {
			if (checkValid(r)==false) continue;
			for (int c = 1; c <= M; c++) {
				int nextC = c - k;
				if (nextC <= 0) nextC += M;
				ntable[r][nextC] = table[r][c];
			}
		}
	}
	memcpy(table, ntable, sizeof(table));
	// printTable();
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d %d %d", &N, &M, &T);

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++) {
			scanf("%d", &table[r][c]);
		}
	}

	int x, d, k;
	Rot rot;
	for (int i = 0; i < T; i++) {
		scanf("%d %d %d", &x, &d, &k);
		rot = { x,d,k };
		rotInfo.push_back(rot);
	}
	
	for (int i = 0; i < T; i++) {
		rotateCircle(rotInfo[i].x, rotInfo[i].d, rotInfo[i].k);
		removeNumber();
	}

	int ans = 0;
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= M; c++)
			ans += table[r][c];
	}
	printf("%d\n", ans);
}