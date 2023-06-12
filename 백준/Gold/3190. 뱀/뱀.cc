#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct _node {
	int x;
	int y;
	int head; // head(0): 오른쪽, head(1): 왼쪽, head(2): 아래쪽, head(3): 위쪽
} Node;

// 방향에 따른 dx, dy
int movement[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int change_direction(int head, char c) {

	switch (head) {
	case 0:
		if (c == 'D') return 2;
		else if (c == 'L') return 3;
		else return head;
		break;
	case 1:
		if (c == 'D') return 3;
		else if (c == 'L') return 2;
		else return head;
		break;
	case 2:
		if (c == 'D') return 1;
		else if (c == 'L') return 0;
		else return head;
		break;
	case 3:
		if (c == 'D') return 0;
		else if (c == 'L') return 1;
		else return head;
		break;
	}
}

// 빈칸(0)이면 해당 좌표를 큐에 담고, q[0]을 pop하여 tail을 바꿔준다.
// 자기자신(1)이면 탐색을 종료한다.
// 사과(2)이면 해당 좌표를 큐에 담는다.
bool update_board(vector<vector<int>>& board, queue<Node>& q, int head, int x, int y) {
	int N = board[0].size() - 1;
	if (x >= 1 && x <= N && y >= 1 && y <= N) {
		if (board[x][y] == 0) {
			board[x][y] = 1;
			board[q.front().x][q.front().y] = 0;

			Node nnode = { x, y, head };
			q.push(nnode);
			q.pop();
			return true;
		}
		else if (board[x][y] == 1) {
			return false;
		}
		else if (board[x][y] == 2) {
			board[x][y] = 1;
			Node nnode = { x, y, head };
			q.push(nnode);
			return true;
		}
	}
	else return false;
}

int move_snake(vector<vector<int>>& board, vector<char>& direction, queue<Node>& q) {
	int time = 0;

	int cur_head = q.back().head;
	int next_head = cur_head;
	while (true) {
		time += 1;
		cur_head = next_head;
		int next_x = q.back().x + movement[cur_head][0];
		int next_y = q.back().y + movement[cur_head][1];
		if (update_board(board, q, cur_head, next_x, next_y) == false) break;
		next_head = change_direction(cur_head, direction[time]);
	}

	return time;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N;
	cin >> N;
	// 빈칸(0), 뱀(1), 사과(2)
	vector<vector<int>> board(N+1, vector<int>(N+1, 0));

	int K;
	cin >> K;
	for (int line = 0; line < K; line++) {
		int x, y;
		cin >> x >> y;
		board[x][y] = 2;
	}

	int L;
	cin >> L;
	vector<char> direction(10001);
	
	for (int line = 0; line < L; line++) {
		int x; char c;
		cin >> x >> c;
		direction[x] = c;
	}

	queue<Node> q;
	Node first = { 1, 1, 0 }; // 초기 상태(x=1, y=1, head=0)
	q.push(first);

	int ans = move_snake(board, direction, q);
	cout << ans << endl;
	return 0;
}