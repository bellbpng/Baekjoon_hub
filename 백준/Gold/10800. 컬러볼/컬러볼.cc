#include <iostream>
#include <vector>
#include <algorithm>
#include <memory.h>
using namespace std;

typedef struct _ball {
	int color, size, idx;
} Ball;

vector<Ball> ballList;
int szColor[200001];
int answer[200001];
int sameSz[200001];

bool cmp(Ball b1, Ball b2) {
	if (b1.size != b2.size)
		return b1.size < b2.size;
	else
		return b1.color < b2.color;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	
	int N;
	scanf("%d", &N);
	Ball iball;
	for (int i = 1; i <= N; i++) {
		scanf("%d %d", &iball.color, &iball.size);
		iball.idx = i;
		ballList.push_back(iball);
	}
	// 크기와 색깔 번호가 작은 공부터 사로잡을 수 있는 공들을 찾는다.
	sort(ballList.begin(), ballList.end(), cmp);

	memset(szColor, 0, sizeof(szColor));
	memset(answer, 0, sizeof(answer));
	memset(sameSz, 0, sizeof(sameSz));
	int sum = 0;
	for (int i = 0; i < ballList.size(); i++) {
		int color = ballList[i].color;
		int sz = ballList[i].size;
		int idx = ballList[i].idx;

		answer[idx] = sum - szColor[color] - sameSz[sz];
		// 색깔, 크기가 동일한 공의 경우 이전 공과 같은 결과를 담는다.
		if (i > 0 && (ballList[i - 1].color == color) && (ballList[i - 1].size == sz))
			answer[idx] = answer[ballList[i - 1].idx];

		sum += sz;
		szColor[color] += sz; // 색깔이 같은 공들의 무게 합
		sameSz[sz] += sz; // 크기가 같은 공들의 무게 합

		
	}
	for (int i = 1; i <= N; i++) 
		printf("%d\n", answer[i]);
}