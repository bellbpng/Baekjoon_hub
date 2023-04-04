#include <iostream>
#include <vector>
#include <memory.h>
#include <queue>
using namespace std;

typedef struct _point
{
	int x;
	int y;
} Point;

int n, m;
int origin_map[8][8];
int new_map[8][8]; // 새롭게 세운 벽을 나타낼 map
int max_safe_zone = 0;

vector<Point> blank;
Point sub_blank[3];
bool dfs_visited[64] = { false, };
// bool bfs_visited[8][8] = { false, };


// 상, 하, 좌, 우
int dx[4] = { -1,1,0,0 }; 
int dy[4] = { 0,0,-1,1 };

void copy_map()
{
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			new_map[r][c] = origin_map[r][c];
}

// 빈칸 좌표 담기
void find_blank_space()
{
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			if (origin_map[r][c] == 0)
			{
				Point pos = { r,c };
				blank.push_back(pos);
			}
}

// 빈칸 개수 세기
int num_safe_zone()
{
	int cnt = 0;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			if (new_map[r][c] == 0)
				cnt++;

	return cnt;
}

void bfs(Point v)
{
	// memset(bfs_visited, false, sizeof(bfs_visited));

	queue<Point> q;
	q.push(v);
	int xpos = v.x; 
	int ypos = v.y;
	// bfs_visited[xpos][ypos] = true;

	while (!q.empty())
	{
		Point pos = q.front();
		q.pop();

		int next_x, next_y;
		for (int i = 0; i < 4; i++)
		{
			next_x = pos.x + dx[i];
			next_y = pos.y + dy[i];
			if ((next_x >= 0 && next_x < n) && (next_y >= 0 && next_y < m))
			{
				if (new_map[next_x][next_y]==0) // 인접한 노드가 빈칸이라면
				{
					// bfs_visited[next_x][next_y] = true;
					new_map[next_x][next_y] = 2; // 바이러스 전염
					Point npos = { next_x, next_y };
					q.push(npos);
				}
			}
		}
	}

}

void dfs(int v, int cnt)
{
	if (cnt == 3)
	{
		copy_map(); // new_map에 origin_map 덮어쓰기
		// 벽세우기
		for (int i = 0; i < 3; i++)
		{
			int xpos = sub_blank[i].x;
			int ypos = sub_blank[i].y;
			new_map[xpos][ypos] = 1;
		}
		// 바이러스 전파 (bfs)
		for(int r=0; r<n; r++)
			for (int c = 0; c < m; c++)
			{
				if (new_map[r][c] == 2)
				{
					Point pos = { r,c };
					bfs(pos);
				}
			}

		// 0의 개수 세기
		int max_candidate = num_safe_zone();
		if (max_safe_zone < max_candidate)
			max_safe_zone = max_candidate;

		return;
	}

	for (int i = v; i < blank.size(); i++)
	{
		if (!dfs_visited[i])
		{
			dfs_visited[i] = true;
			Point pos = { blank[i].x, blank[i].y };
			sub_blank[cnt] = pos;
			dfs(i + 1, cnt + 1);
			dfs_visited[i] = false;
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	// map 초기화
	cin >> n >> m;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cin >> origin_map[r][c];

	find_blank_space();
	dfs(0, 0);

	cout << max_safe_zone << endl;
	return 0;
}