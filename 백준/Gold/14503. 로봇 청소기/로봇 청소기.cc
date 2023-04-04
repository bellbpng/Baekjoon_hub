#include <iostream>
#include <memory.h>
using namespace std;

int n, m;
int x, y, head; // head 0: north, 1: east, 2: south, 3: west
int map[50][50];

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

bool move_back() 
{
	int next_x = x; 
	int next_y = y;

	switch (head)
	{
	case 0: // north
		next_x = x + 1;
		break;
	case 1: // east
		next_y = y - 1;
		break;
	case 2: // south
		next_x = x - 1;
		break;
	case 3: // west
		next_y = y + 1;
		break;
	}
	
	if ((next_x >= 0 && next_x < n) && (next_y >= 0 && next_y < m))
	{
		if (map[next_x][next_y] == 1)
			return false; // 후진했을 때 벽인 경우

		x = next_x;
		y = next_y;

		return true; // 후진 성공
	}
}

bool check_around()
{
	int next_x, next_y;

	for (int i = 0; i < 4; i++)
	{
		next_x = x + dx[i];
		next_y = y + dy[i];
		if ((next_x >= 0 && next_x < n) && (next_y >= 0 && next_y < m))
		{
			if (map[next_x][next_y] == 0)
				return true; // 주변 4칸에 청소할 곳이 있을 때
		}
	}
	return false; // 주변 4칸에 청소할 곳이 없을 때
}

void turn_head_90()
{
	switch (head)
	{
	case 0: // north
		head = 3;
		break;
	case 1: // east
		head = 0;
		break;
	case 2: // south
		head = 1;
		break;
	case 3: // west
		head = 2;
		break;
	}
}

void move_forward()
{
	int next_x = x;
	int next_y = y;

	switch (head)
	{
	case 0: // north
		next_x = x - 1;
		break;
	case 1: // east
		next_y = y + 1;
		break;
	case 2: // south
		next_x = x + 1;
		break;
	case 3: // west
		next_y = y - 1;
		break;
	}

	if ((next_x >= 0 && next_x < n) && (next_y >= 0 && next_y < m))
	{
		if (map[next_x][next_y] == 0)
		{
			x = next_x;
			y = next_y;
		}
	}
}

int proc_cleaner()
{
	int cnt = 0; // 청소한 칸의 개수

	while (true)
	{
		// 현재 칸 청소
		if (map[x][y] == 0)
		{
			map[x][y] = 2; // 청소하면 2
			cnt++;
		}

		// 주변 4칸 확인
		if (check_around())
		{
			turn_head_90();
			move_forward();
		}
		else
		{
			if (!move_back())
				break;
		}
	}
	return cnt;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	cin >> x >> y >> head;

	// map 초기화
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cin >> map[r][c];

	int ans = proc_cleaner();
	cout << ans << endl;

	return 0;
}
