#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool CheckLadder(vector<vector<int>>& ladder) {
	int h = ladder.size(); // 가로 점선
	int n = ladder[0].size(); // 세로선

	for (int c = 1; c < n-1; c++) { // 1 ~ n-1
		int ccol = c;
		for (int r = 1; r < h; r++) { // 1 ~ h
			int left = ccol - 1;
			if (ladder[r][left] == 1) ccol = left;
			else if (ladder[r][ccol] == 1) ccol++;
		}
		if (ccol != c) return false;
	}
	return true;
}

void Dfs(vector<vector<int>>& ladder, int cnt, int m, bool& flag) {
	// 기저사례: 이미 답을 구한 경우
	if (flag) return;

	// 기저사례: cnt==m, 추가 사다리를 모두 놓은 경우
	if (cnt == m) {
		if (CheckLadder(ladder)) {
			flag = true;
			return;
		}
		return;
	}
	
	int h = ladder.size(); // h+1
	int n = ladder[0].size();
	for (int c = 1; c < n-1; c++) { // 1 ~ n-1
		for (int r = 1; r < h; r++) { // 1~h
			int left = c - 1;
			int right = c + 1;
			if (ladder[r][left] || ladder[r][right] || ladder[r][c]) continue;
			ladder[r][c] = 1;
			Dfs(ladder, cnt + 1, m, flag);
			ladder[r][c] = 0;
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int N, M, H, a, b;
	cin >> N >> M >> H;

	// b번 세로선과, b+1번 세로선을 a번 점선 위치에서 연결
	// ladder[a][b] = 1
	vector<vector<int>> ladder(H + 1, vector<int>(N+1, 0));
	for (int i = 0; i < M; i++) {
		cin >> a >> b;
		ladder[a][b] = 1;
	}

	bool flag = false;
	int ans = -1;
	for (int m = 0; m < 4; m++) {
		Dfs(ladder, 0, m, flag);
		if (flag) {
			ans = m;
			break;
		}
	}
	cout << ans << endl;
	return 0;

}