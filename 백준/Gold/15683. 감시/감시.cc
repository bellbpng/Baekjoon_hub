#include <iostream>
#include <memory.h>
using namespace std;

typedef struct _dir // 방향 정보
{
	int up;
	int down;
	int left;
	int right;
} Dir;

typedef struct _node
{
	int cctv; // cctv number
	int n_type; // 탐색 유형개수
	Dir* head;
	int xpos, ypos; // cctv 위치
} Node;

typedef struct _flag
{
	int cctv;
	int head[4];
} Flag;

int n, m;
int origin_map[8][8]; // 0: 빈칸, 1~5: CCTV 번호, 6: 벽, -1: #
int cmap[8][8];
int ans = 100;
int cnt_wall = 0;
int num_five_cctv = 0;

// for dfs
Node node[8];
Node cnode[8];
Flag visited[8];
int node_num;

Dir cctv_1[4]; // 상, 우, 하, 좌
Dir cctv_2[2]; // 좌우, 상하
Dir cctv_3[4]; // 상우, 상좌, 하좌, 하우
Dir cctv_4[4]; // 상좌우, 상하좌, 하좌우, 상하우

// cctv별 유형 개수
int t_cctv1 = 4;
int t_cctv2 = 2;
int t_cctv3 = 4;
int t_cctv4 = 4;


/********************************************************************************/

// Debugging
int dfs_cnt = 0;
void print_map()
{
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
			cout << cmap[r][c] << " ";
		cout << endl;
	}
	cout << endl;
}

// 각 경우의 수 마다 map을 초기화하여야한다.
void copy_map()
{
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cmap[r][c] = origin_map[r][c];
}

void init_cctv() // cctv별 유형을 정리하고, 개수를 파악한다.
{
	// cctv1
	cctv_1[0] = { 1,0,0,0 }; cctv_1[1] = { 0,0,0,1 };
	cctv_1[2] = { 0,1,0,0 }; cctv_1[3] = { 0,0,1,0 };

	// cctv2
	cctv_2[0] = { 0,0,1,1 }; cctv_2[1] = { 1,1,0,0 };

	// cctv3
	cctv_3[0] = { 1,0,0,1 }; cctv_3[1] = { 1,0,1,0 };
	cctv_3[2] = { 0,1,1,0 }; cctv_3[3] = { 0,1,0,1 };
	
	// cctv4
	cctv_4[0] = { 1,0,1,1 }; cctv_4[1] = { 1,1,1,0 };
	cctv_4[2] = { 0,1,1,1 }; cctv_4[3] = { 1,1,0,1 };

}

void make_node()
{
	// node: cctv number, 유형 개수, 탐색 유형, 좌표
	int idx = 0;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			if (origin_map[r][c] == 1)
			{
				node[idx++] = { 1, t_cctv1, cctv_1, r, c };
			}
			else if (origin_map[r][c] == 2)
			{
				node[idx++] = { 2, t_cctv2, cctv_2, r, c };
			}
			else if (origin_map[r][c] == 3)
			{
				node[idx++] = { 3, t_cctv3, cctv_3, r, c };
			}
			else if (origin_map[r][c] == 4)
			{
				node[idx++] = { 4, t_cctv4, cctv_4, r, c };
			}
			else if (origin_map[r][c] == 5)
			{
				num_five_cctv += 1;
				// 상,하,좌,우 모두 #처리 -> 벽, 다른 cctv 고려
				int y = c;
				// 상
				for (int x = r - 1; x >= 0; x--)
				{
					if (origin_map[x][y] == 6)
						break;
					if (origin_map[x][y] >= 1 && origin_map[x][y] <= 5)
						continue;
					origin_map[x][y] = -1;
				}
				// 하
				for (int x = r + 1; x < n; x++)
				{
					if (origin_map[x][y] == 6)
						break;
					if (origin_map[x][y] >= 1 && origin_map[x][y] <= 5)
						continue;
					origin_map[x][y] = -1;
				}

				int x = r;
				// 좌
				for (int y = c - 1; y >= 0; y--)
				{
					if (origin_map[x][y] == 6)
						break;
					if (origin_map[x][y] >= 1 && origin_map[x][y] <= 5)
						continue;
					origin_map[x][y] = -1;
				}
				// 우
				for (int y = c + 1; y < m; y++)
				{
					if (origin_map[x][y] == 6)
						break;
					if (origin_map[x][y] >= 1 && origin_map[x][y] <= 5)
						continue;
					origin_map[x][y] = -1;
				}
			}
			else if (origin_map[r][c] == 6)
				cnt_wall += 1;
		}
	}
	node_num = idx;
	if (node_num == 0)
	{
		int cnt = 0;
		for (int r = 0; r < n; r++)
		{
			for (int c = 0; c < m; c++)
			{
				if (origin_map[r][c] == 0)
					cnt++;
			}
		}
		ans = cnt;
	}

	for (int i = 0; i < node_num; i++)
	{
		int cctv_type = node[i].cctv;
		switch (cctv_type)
		{
		case 1:
			node[i].n_type = t_cctv1;
			break;
		case 2:
			node[i].n_type = t_cctv2;
			break;
		case 3:
			node[i].n_type = t_cctv3;
			break;
		case 4:
			node[i].n_type = t_cctv4;
			break;
		}
	}

	// Debugging
	// cout << endl << "node 개수: ";
	// cout << node_num << endl;

}

void search_map(int num) // node가 없으면 실행되지 않는 함수
{
	Dir nhead = *(cnode[num].head);

		if (nhead.up == 1)
		{
			// x감소, y고정
			int c = cnode[num].ypos;
			for (int r = cnode[num].xpos - 1; r >= 0; r--)
			{
				if (cmap[r][c] == 6) // 벽을 만나는 경우
					break;
				if (cmap[r][c] >= 1 && cmap[r][c] <= 5) // 다른 cctv를 만나는 경우
					continue;

				if (cmap[r][c] == 0)
					cmap[r][c] = -1; // # 처리
			}
		}
		if (nhead.down == 1)
		{
			// x증가, y고정
			int c = cnode[num].ypos;
			for (int r = cnode[num].xpos + 1; r < n; r++)
			{
				if (cmap[r][c] == 6) // 벽을 만나는 경우
					break;
				if (cmap[r][c] >= 1 && cmap[r][c] <= 5) // 다른 cctv를 만나는 경우
					continue;

				if (cmap[r][c] == 0)
					cmap[r][c] = -1; // # 처리
			}
		}
		if (nhead.left == 1)
		{
			// x고정, y감소
			int r = cnode[num].xpos;
			for (int c = cnode[num].ypos - 1; c >= 0; c--)
			{
				if (cmap[r][c] == 6) // 벽을 만나는 경우
					break;
				if (cmap[r][c] >= 1 && cmap[r][c] <= 5) // 다른 cctv를 만나는 경우
					continue;

				if (cmap[r][c] == 0)
					cmap[r][c] = -1; // # 처리
			}
		}
		if (nhead.right == 1)
		{
			// x고정, y증가
			int r = cnode[num].xpos;
			for (int c = cnode[num].ypos + 1; c <m; c++)
			{
				if (cmap[r][c] == 6) // 벽을 만나는 경우
					break;
				if (cmap[r][c] >= 1 && cmap[r][c] <= 5) // 다른 cctv를 만나는 경우
					continue;

				if (cmap[r][c] == 0)
					cmap[r][c] = -1; // # 처리
			}
	}

	int cnt = 0;
	for (int r = 0; r < n; r++)
	{
		for (int c = 0; c < m; c++)
		{
			if (cmap[r][c] == 0)
				cnt++;
		}
	}
	
	if (ans > cnt)
		ans = cnt;
}

void dfs(int v)
{
	if (v == node_num) // 모든 노드를 방문해서 순서 정해지면 탈출
	{
		// map 탐색 -> # 처리
		copy_map();
		for (int i = 0; i < node_num; i++)
		{
			search_map(i);
		}

		// Debugging
		dfs_cnt++;
		// if(dfs_cnt<5)
			// print_map();

		return;
	}

	for (int i = 0; i < node[v].n_type; i++) // 노드의 cctv 번호에 해당하는 유형 개수만큼 각각 탐색
	{
		if (visited[v].head[i] == 0)
		{
			visited[v].head[i] = 1; // 방문표시
			cnode[v].cctv = node[v].cctv;
			cnode[v].head = node[v].head + i; // 포인터 연산
			cnode[v].n_type = node[v].n_type;
			cnode[v].xpos = node[v].xpos;
			cnode[v].ypos = node[v].ypos;
			dfs(v + 1);
			visited[v].head[i] = 0; // 방문표시 해제
		}
	}

}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> n >> m;
	for (int r = 0; r < n; r++)
		for (int c = 0; c < m; c++)
			cin >> origin_map[r][c];

	init_cctv();
	make_node();
	for (int i = 0; i < 8; i++)
		memset(visited[i].head, 0, sizeof(int) * 4);
	dfs(0);

	// Debugging
	// cout << "dfs 실행 횟수: ";
	// cout << dfs_cnt << endl << endl;

	cout << ans << endl;

	return 0;
}