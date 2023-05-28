#include <iostream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

int N;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
int cnt_recur = 0;

// 유효한 좌표인지 확인한다.
bool check_valid(int xpos, int ypos)
{
	if (xpos >= 0 && xpos < N && ypos >= 0 && ypos < N)
		return true;
	else
		return false;
}

void set_area(vector<string>& map, int xpos, int ypos, char color)
{
	cnt_recur++;

	// 상하좌우 4가지 방향으로 이동하며 재귀호출을 통한 완전탐색
	for (int dir = 0; dir < 4; dir++)
	{
		map[xpos][ypos] = '*'; // 구역 번호 설정
		int next_x = xpos + dx[dir];
		int next_y = ypos + dy[dir];

		// 지도를 벗어나는 좌표의 경우 스킵
		if (check_valid(next_x, next_y) == false) continue;
		// 구역이 정해진 칸은 스킵
		if (!isalpha(map[next_x][next_y])) continue;
		// 이동한 좌표의 색상이 다른 경우 스킵
		if (color != map[next_x][next_y]) continue;
		set_area(map, next_x, next_y, color);
	}
	return;
}

void find_num_area(vector<string>& normal_map, vector<string>& weak_color_map)
{
	int normal_cnt = 0;
	int weak_color_cnt = 0;

	// 칸에 적힌 문자가 알파벳 문자(R,G,B)이면 구역을 만들기 위해 set_area 함수를 호출하고,
	// 칸에 적힌 문자가 숫자 문자(1, 2, ...) 이면 구역이 정해졌으므로 아무것도 하지 않는다.
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			if (isalpha(normal_map[r][c]))
			{
				normal_cnt++;
				set_area(normal_map, r, c, normal_map[r][c]);
			}
			if (isalpha(weak_color_map[r][c]))
			{
				weak_color_cnt++;
				set_area(weak_color_map, r, c, weak_color_map[r][c]);
			}
		}
	}

	cout << normal_cnt << " " << weak_color_cnt << endl;
}

void print_map(vector<string>& map1, vector<string>& map2)
{
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			cout << map1[r][c];
		}
		cout << endl;
	}
	cout << "----------------------------" << endl;
	for (int r = 0; r < N; r++)
	{
		for (int c = 0; c < N; c++)
		{
			cout << map2[r][c];
		}
		cout << endl;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> N;

	vector<string> normal_map(N);
	vector<string> weak_color_map(N);
	string str;
	for (int line = 0; line < N; line++)
	{
		cin >> str;
		normal_map[line] = str;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == 'G') // 색약이 있는 경우 R과 G는 같은 색이다.
				str[i] = 'R';
		}
		weak_color_map[line] = str; // 색약이 있는 사람이 보는 맵
	}

	find_num_area(normal_map, weak_color_map);
	// print_map(normal_map, weak_color_map);
	// cout << cnt_recur << endl;
	return 0;
}