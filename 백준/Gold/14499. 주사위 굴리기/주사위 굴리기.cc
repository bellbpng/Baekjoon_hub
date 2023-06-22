#include <iostream>
using namespace std;

int n, m, x, y, k;
int dice[6] = { 0, };
int map[20][20];

void init_dice(int top, int bottom, int east, int west, int south, int north)
{
	int tmp[6] = { dice[top], dice[bottom], dice[east], dice[west], dice[south], dice[north] };
	
	// 주사위 면 초기화
	for (int i = 0; i < 6; i++)
		dice[i] = tmp[i];
}



void move_dice(int dir)
{
	switch (dir)
	{
	case 1: // east
		if (y + 1 < m)
		{
			y++;
			init_dice(3, 2, 0, 1, 4, 5);
			if (map[x][y] == 0)
				map[x][y] = dice[1];
			else
			{
				dice[1] = map[x][y];
				map[x][y] = 0;
			}
			
			cout << dice[0] << endl;
		}
		break;
	case 2: // west
		if (y - 1 >= 0)
		{
			y--;
			init_dice(2, 3, 1, 0, 4, 5);
			if (map[x][y] == 0)
				map[x][y] = dice[1];
			else
			{
				dice[1] = map[x][y];
				map[x][y] = 0;
			}
			
			cout << dice[0] << endl;
		}
		break;
	case 3: // north
		if (x - 1 >= 0)
		{
			x--;
			init_dice(4, 5, 2, 3, 1, 0);
			if (map[x][y] == 0)
				map[x][y] = dice[1];
			else
			{
				dice[1] = map[x][y];
				map[x][y] = 0;
			}
			
			cout << dice[0] << endl;
		}
		break;
	case 4: // south
		if (x + 1 < n)
		{
			x++;
			init_dice(5, 4, 2, 3, 0, 1);
			if (map[x][y] == 0)
				map[x][y] = dice[1];
			else
			{
				dice[1] = map[x][y];
				map[x][y] = 0;
			}
			
			cout << dice[0] << endl;
		}
		break;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m >> x >> y >> k;

	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cin >> map[r][c];

	int dir;
	for (int i = 0; i < k; i++)
	{
		cin >> dir;
		move_dice(dir);
	}

	return 0;
}

