#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct MyPair { int x, y; MyPair(int a, int b) :x(a), y(b) {} };
vector<pair<int, int>> moveCmd = { {-2, 1},{-1, 2},{1, 2},{2, 1},{2, -1},{1, -2},{-1, -2},{-2, -1} };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int testcase;
	cin >> testcase;

	while (testcase--)
	{
		int N, x, y, a, b;
		cin >> N >> x >> y >> a >> b;

		vector<vector<int>> field(N, vector<int>(N, 100000));
		queue<MyPair> q;

		field[x][y] = 0;
		q.push({ x,y });

		while (!q.empty())
		{
			MyPair curr = q.front();
			q.pop();

			for (auto& move : moveCmd)
			{
				int nextX = curr.x + move.first;
				int nextY = curr.y + move.second;

				if ((0 <= nextX && nextX < N) && (0 <= nextY && nextY < N))
				{
					if (field[nextX][nextY] > field[curr.x][curr.y] + 1)
					{
						field[nextX][nextY] = field[curr.x][curr.y] + 1;
						q.push({ nextX, nextY });
					}
				}
			}
		}

		cout << field[a][b] << '\n';
	}

	return 0;
}