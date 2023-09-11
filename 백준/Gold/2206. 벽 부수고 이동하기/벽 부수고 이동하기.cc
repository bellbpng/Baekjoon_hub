#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
#include <memory.h>
using namespace std;

// status 는 벽을 부셨는지를 확인. 1이면 이미 벽을 하나 부순 상태
typedef struct _pos {
	int xpos, ypos, status;
} Pos;

int N, M;
vector<string> board;
// [x][y][0]: (x,y)까지 벽을 부수지 않았을 때 최소 비용
// [x][y][1]: (x,y)까지 벽을 부수고 왔을 때 최소 비용
int dist[1000][1000][2]; 
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };

int bfs(int sx, int sy) {
	memset(dist, 0, sizeof(dist));
	queue<Pos> q;
	q.push({ sx, sy, 0 });
	dist[sx][sy][0] = 1;
	dist[sx][sy][1] = 1;
	
	while (!q.empty()) {
		Pos cpos = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cpos.xpos + dx[dir];
			int ny = cpos.ypos + dy[dir];
			int status = cpos.status;
			if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
			if (board[nx][ny] == '0') {
				if (dist[nx][ny][status] == 0) {
					q.push({ nx, ny, status });
					dist[nx][ny][status] = dist[cpos.xpos][cpos.ypos][cpos.status] + 1;
				}
				else {
					if (dist[nx][ny][status] > dist[nx][ny][status] + 1) {
						q.push({ nx, ny, status });
						dist[nx][ny][status] = dist[cpos.xpos][cpos.ypos][cpos.status] + 1;
					}
				}
			}
			else if (board[nx][ny] == '1') {
				if (cpos.status == 0) {
					if (dist[nx][ny][1] == 0) {
						q.push({ nx, ny, 1 });
						dist[nx][ny][1] = dist[cpos.xpos][cpos.ypos][cpos.status] + 1;
					}
					else {
						if (dist[nx][ny][1] > dist[cpos.xpos][cpos.ypos][cpos.status] + 1) {
							q.push({ nx, ny, 1 });
							dist[nx][ny][1] = dist[cpos.xpos][cpos.ypos][cpos.status] + 1;
						}
					}
				}
			}
		}
	}
	if (dist[N-1][M-1][0] == 0 && dist[N-1][M-1][1] == 0) return -1;
	else if (dist[N - 1][M - 1][0] == 0) return dist[N - 1][M - 1][1];
	else if (dist[N - 1][M - 1][1] == 0) return dist[N - 1][M - 1][0];
	else return min(dist[N - 1][M - 1][0], dist[N - 1][M - 1][1]);
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	cin >> N >> M;
	string str;
	for (int i = 0; i < N; i++) {
		cin >> str;
		board.push_back(str);
	}
	int answer = bfs(0, 0);
	printf("%d\n", answer);
	return 0;
}