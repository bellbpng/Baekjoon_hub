#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;

typedef struct _ele
{
	int pos;
	int time;
} Ele;

bool visited[100001]; // 방문표시

bool check_valid(int pos)
{
	if (0 <= pos && pos <= 100000 && visited[pos]==false)
		return true;
	else
		return false;
}

int bfs(int x, int k)
{
	memset(visited, false, sizeof(visited));

	Ele el = { x, 0 }; // 처음 위치와 시간 정보
	int next_pos1, next_pos2, next_pos3, time;
	queue<Ele> q;
	q.push(el);

	while (!q.empty())
	{
		el = q.front();
		time = el.time;
		visited[el.pos] = true;
		q.pop();

		if (el.pos == k)
			return el.time;

		next_pos1 = el.pos - 1;
		next_pos2 = el.pos + 1;
		next_pos3 = el.pos * 2;

		if (check_valid(next_pos1))
		{
			el.pos = next_pos1;
			el.time = time + 1;
			q.push(el);
		}
		if (check_valid(next_pos2))
		{
			el.pos = next_pos2;
			el.time = time + 1;
			q.push(el);
		}
		if (check_valid(next_pos3))
		{
			el.pos = next_pos3;
			el.time = time + 1;
			q.push(el);
		}
	}
}


int main()
{
	int n, k; // 수빈이의 처음 위치(n), 동생의 위치(k)
	cin >> n >> k;

	int ans = bfs(n, k);

	cout << ans << endl;
	return 0;
}