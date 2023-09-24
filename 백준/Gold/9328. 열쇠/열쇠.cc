#include <iostream>
#include <string>
#include <vector>
#include <memory.h>
#include <queue>
#include <cctype>
using namespace std;

int H, W;
vector<string> board;
int dx[4] = { -1, 1, 0, 0 };
int dy[4] = { 0, 0, -1, 1 };
bool keys[26];
bool checked[102][102]; // 이미 획득한 $ 인지 확인
int ans = 0;

void printBoard() {
	cout << "------------------------\n";
	for (auto ele : board) {
		cout << ele << endl;
	}
}

void bfs(int sx, int sy) {
	// 열쇠가 없어서 열지 못한 문의 좌표를 담는다.
	// door[0][idx].first, door[0][idx].second 는 열지 못한 idx번 문 A의 좌표를 담는다.
	queue<pair<int, int>> door[26];
	queue<pair<int, int>> q;
	bool visited[102][102];
	memset(visited, false, sizeof(visited));
	q.push(make_pair(sx, sy));
	visited[sx][sy] = true;

	while (!q.empty()) {
		pair<int, int> cpos = q.front();
		q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = cpos.first + dx[dir];
			int ny = cpos.second + dy[dir];
			if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
			if (board[nx][ny] == '*') continue;
			if (visited[nx][ny]) continue;
			// 문을 만난 경우
			if (isupper(board[nx][ny])) {
				// 열쇠가 있어서 열 수 있는 경우
				char ch = tolower(board[nx][ny]);
				if (keys[ch - 'a']) {
					visited[nx][ny] = true;
					q.push(make_pair(nx, ny));
				}
				// 열쇠가 없어서 열 수 없는 경우
				else {
					door[board[nx][ny] - 'A'].push(make_pair(nx, ny));
				}
			}
			// 열쇠를 주운 경우
			else if (islower(board[nx][ny])) {
				int idx = board[nx][ny] - 'a';
				keys[idx] = true;
				visited[nx][ny] = true;
				q.push(make_pair(nx, ny));
				// 이전에 열지 못한 문이 있는 경우 bfs 큐에 넣어서 다시 탐색할 수 있도록 한다.
				while (!door[idx].empty()) {
					q.push(door[idx].front());
					door[idx].pop();
				}
			}
			// 문서를 훔친 경우
			else if (board[nx][ny] == '$') {
				checked[nx][ny] = true;
				ans++;
				visited[nx][ny] = true;
				q.push(make_pair(nx, ny));
			}
			else if (board[nx][ny] == '.') {
				visited[nx][ny] = true;
				q.push(make_pair(nx, ny));
			}
		}
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;

	for (int test_case = 0; test_case < T; test_case++) {
		int h, w;
		cin >> h >> w;
		H = h + 2, W = w + 2;
		board.clear();
		memset(keys, false, sizeof(keys));
		memset(checked, false, sizeof(checked));
		ans = 0;
		board.push_back(string(W, '.'));
		string str;
		for (int i = 0; i < h; i++) {
			cin >> str;
			str.push_back('.');
			str.insert(str.begin(), '.');
			board.push_back(str);
		}
		board.push_back(string(W, '.'));

		// input key
		cin >> str;
		if (str != "0") {
			for (auto ele : str) {
				keys[ele - 'a'] = true;
			}
		}
		// printBoard();

		// 모든 입구에 대해서 bfs
		bfs(0, 0);
		printf("%d\n", ans);
	}
	return 0;
}