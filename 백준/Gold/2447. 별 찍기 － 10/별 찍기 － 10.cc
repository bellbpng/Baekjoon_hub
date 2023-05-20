#include <iostream>
#include <vector>
using namespace std;

// pattern을 정사각형 배열에 입력하는 재귀함수
// 좌측상단에 위치하는 시작좌표와 다음 좌표로 이동하는 간격 step을 인자로 받는다.
// step==1인 경우 3x3 기본 패턴을 입력한다.
// 정사각형에서 중앙에 위치(5번째 탐색 칸)하는 칸은 공백으로 두어야 한다.
void make_pattern(vector<vector<char>>& square, int start_x, int start_y, int step)
{
	// 기저사례
	if (step == 1)
	{
		int flag = 0; // 5번째 입력하는 경우는 공백으로 둔다.
		for (int r = start_x, cnt_x=0; cnt_x<3; r++, cnt_x++)
		{
			for (int c = start_y, cnt_y=0; cnt_y < 3; c++, cnt_y++)
			{
				flag += 1;
				if (flag == 5) continue;
				square[r][c] = '*';
			}
		}
		return;
	}
	
	int flag = 0;
	for (int r = start_x, cnt_x = 0; cnt_x < 3; r += step, cnt_x++)
	{
		for (int c = start_y, cnt_y = 0; cnt_y < 3; c += step, cnt_y++)
		{
			flag += 1;
			if (flag == 5) continue;
			make_pattern(square, r, c, step / 3);
		}
	}
	return;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;
	vector<vector<char>> square(N+1, vector<char>(N+1, ' ')); // 공백 문자로 채워진 2차원 배열을 형성
	make_pattern(square, 1, 1, N / 3);
	
	for (int r = 1; r <= N; r++)
	{
		for (int c = 1; c <= N; c++)
			cout << square[r][c];
		cout << endl;
	}
	return 0;
}