#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

int N;
int cand[9]; // cand[8]=1 : 4번 타자는 1번 선수로 고정
bool visited[8] = { false, };
int player[8] = { 2, 3, 4, 5, 6, 7, 8, 9 };
int table[51][10]; // 1번 선수부터 9번 선수까지 이닝별 결과

int playGame() {
	// 타순 설정
	int hitPlayers[10];
	for (int i = 0; i < 3; i++) {
		hitPlayers[i + 1] = cand[i];
	}
	// 4번 타자 고정
	hitPlayers[4] = cand[8];
	for (int i = 3; i < 8; i++) {
		hitPlayers[i + 2] = cand[i];
	}

	int runner[4] = { 0, 0, 0, 0 }; // 주자 상태
	int ret = 0;
	int idx = 1;
	for (int inning = 1; inning <= N; inning++) {
		int outCnt = 0;
		memset(runner, 0, sizeof(runner));
		while (true) {
			int number = hitPlayers[idx++];
			int status = table[inning][number];
			// 다음 타순 설정. out count 계산 및 탈출 조건
			if (idx == 10) idx = 1;
			if (status == 0) outCnt++;
			if (outCnt == 3) break;
			
			if (status == 1) {
				// 주자 이동
				for (int i = 3; i >= 1; i--) {
					if (i >= 3 && runner[i]) {
						ret++;
						runner[i] = 0; // 3루수는 들어옴
					}
					else if (runner[i]) {
						runner[i + 1] = 1;
						runner[i] = 0;
					}
				}
				runner[1] = 1; // 타자 이동
			}
			else if (status == 2) {
				for (int i = 3; i >= 1; i--) {
					if (i >= 2 && runner[i]) {
						ret++;
						runner[i] = 0;
					}
					else if (runner[i]) {
						runner[i + 2] = 1;
						runner[i] = 0;
					}
				}
				runner[2] = 1;
			}
			else if (status == 3) {
				for (int i = 3; i >= 1; i--) {
					if (runner[i]) {
						ret++;
						runner[i] = 0;
					}
				}
				runner[3] = 1;
			}
			else if (status == 4) {
				for (int i = 3; i >= 1; i--) {
					if (runner[i]) ret++;
					runner[i] = 0;
				}
				ret++;
			}
		}
	}
	return ret;
}

int setPlayer(int cnt) {
	if (cnt == 8) {
		return playGame();
	}
	
	int ret = 0;
	for (int i = 0; i < 8; i++) {
		if (visited[i]) continue;
		visited[i] = true;
		cand[cnt] = player[i];
		ret = max(ret, setPlayer(cnt + 1));
		visited[i] = false;
	}
	return ret;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int num = 1; num <= 9; num++) {
			scanf("%d", &table[i][num]);
		}
	}
	cand[8] = 1;
	printf("%d\n", setPlayer(0));
}