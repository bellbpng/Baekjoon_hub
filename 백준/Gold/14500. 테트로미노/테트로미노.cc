#include <iostream>
#include <vector>
using namespace std;

int n, m;
int map[500][500];
vector<vector<int>> v(20, vector<int>(4, 0));


void block_init()
{
	v[0] = { 1, 1, 0, 1 }; v[1] = { 4,4,0,4 }; v[2] = { 1,4,0,2 }, v[3] = { 4,4,0,1 };
	v[4] = { 3, 1, 0, 1 }; v[5] = { 1,4,0,4 }; v[6] = { 4,4,0,2 }, v[7] = { 3,3,0,1 };
	v[8] = { 1, 4, 3, 1 }; v[9] = { 4,2,1,1 }; v[10] = { 1,3,4,4 }, v[11] = { 2,3,4,4 };
	v[12] = { 3, 2, 0, 2 }; v[13] = { 4,1,0,1 }; v[14] = { 1,1,0,3 }, v[15] = { 4,1,0,4 };
	v[16] = { 4, 2, 0, 4 }; v[17] = { 1,3,0,1 }; v[18] = { 3,1,0,3 }, v[19] = { 2,3,0,2 };
}

bool check_valid(int xidx, int yidx)
{
	if (xidx >= 0 && xidx < n)
		if (yidx >= 0 && yidx < m)
			return true;

	return false;
}

void change_pos(int k, int vidx, int& x, int& y)
{
	int flag = v[vidx][k];

	switch (flag)
	{
	case 1:
		y++; break;
	case 2:
		y--; break;
	case 3:
		x--; break;
	case 4:
		x++; break;
	default:
		break;
	}

	// cout << x << ", " << y;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> map[i][j];

	block_init();
	
	int xpos, ypos;
	int max_sum = 0, sum;
	for (int i = 0; i < 20; i++)
	{
		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < m; col++)
			{
				xpos = row, ypos = col;
				sum = map[xpos][ypos];
				/*cout << "start idx: " << xpos << ", " << ypos << "| ";
				cout << "start sum: " << sum << endl;*/
				for (int k = 0; k < 4; k++)
				{
					change_pos(k, i, xpos, ypos); // 정사각형 이동
					if (check_valid(xpos, ypos))
					{
						if (k != 2)
							sum += map[xpos][ypos];
						// cout << "| sum: " << sum << endl;
					}
					else
						break;
				}
				if (max_sum < sum)
					max_sum = sum;
			}
		}
	}
	
	cout << max_sum << endl;

	return 0;
}