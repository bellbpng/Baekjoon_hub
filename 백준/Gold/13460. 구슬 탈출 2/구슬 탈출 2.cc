#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

void find_red_blue_pos(vector<string>& board, int& rxpos, int& rypos, int& bxpos, int& bypos) {
	int n = board.size();
	int m = board[0].size();

	for (int r = 0; r < n; r++) {
		for (int c = 0; c < m; c++) {
			if (board[r][c] == 'R') {
				rxpos = r;
				rypos = c;
			}
			else if (board[r][c] == 'B') {
				bxpos = r;
				bypos = c;
			}
		}
	}
}

bool check_hole(vector<string>& board, int xpos, int ypos) {
	if (board[xpos][ypos] == 'O') return true;
	else return false;
}

// 먼저 기울였을 때 움직이게 할 공을 설정한다.
// 빨간공이면 0, 파란공이면 1 반환
int set_priority_ball(int dir, int rxpos, int rypos, int bxpos, int bypos) {

	// 상(0), 하(1), 좌(2), 우(3)
	switch (dir) {
	case 0:
		if (rypos == bypos) {
			if (rxpos < bxpos) return 0;
			else return 1;
		}
		else return 2;
		break;
	case 1:
		if (rypos == bypos) {
			if (rxpos > bxpos) return 0;
			else return 1;
		}
		else return 2;
		break;
	case 2:
		if (rxpos == bxpos) {
			if (rypos < bypos) return 0;
			else return 1;
		}
		else return 2;
		break;
	case 3:
		if (rxpos == bxpos) {
			if (rypos > bypos) return 0;
			else return 1;
		}
		else return 2;
		break;
	}
}

// 모든 기울임의 결과는 좌표를 반환한다.
// 벽이나 다른 색상의 구슬과 부딪힌 경우 이전 빈칸의 좌표를 반환
// 구멍에 위치하게 된 경우 구멍의 좌표를 반환
pair<int, int> move_up(vector<string>& board, int n, int m, int xpos, int ypos) {
	char color = board[xpos][ypos];

	for (int r = xpos; r >= 0; r--) {
		if (board[r][ypos] == '.') continue;
		if (board[r][ypos] == 'O') {
			board[xpos][ypos] = '.';
			return make_pair(r, ypos);
		}
		if (board[r][ypos] == '#' || (board[r][ypos]!='.' && board[r][ypos] != color)) {
			board[xpos][ypos] = '.';
			board[r + 1][ypos] = color;
			return make_pair(r + 1, ypos);
		}
	}
	cout << "Move up error\n";
}

pair<int, int> move_down(vector<string>& board, int n, int m, int xpos, int ypos) {
	char color = board[xpos][ypos];
	for (int r = xpos; r < n; r++) {
		if (board[r][ypos] == '.') continue;
		if (board[r][ypos] == 'O') {
			board[xpos][ypos] = '.';
			return make_pair(r, ypos);
		}
		if (board[r][ypos] == '#' || (board[r][ypos] != '.' && board[r][ypos] != color)) {
			board[xpos][ypos] = '.';
			board[r - 1][ypos] = color;
			return make_pair(r - 1, ypos);
		}
	}
	cout << "Move down error\n";
}

pair<int, int> move_left(vector<string>& board, int n, int m, int xpos, int ypos) {
	char color = board[xpos][ypos];
	for (int c = ypos; c >= 0; c--) {
		if (board[xpos][c] == '.') continue;
		if (board[xpos][c] == 'O') {
			board[xpos][ypos] = '.';
			return make_pair(xpos, c);
		}
		if (board[xpos][c] == '#' || (board[xpos][c] != '.' && board[xpos][c] != color)) {
			board[xpos][ypos] = '.';
			board[xpos][c + 1] = color;
			return make_pair(xpos, c + 1);
		}
	}
	cout << "Move left error\n";
}

pair<int, int> move_right(vector<string>& board, int n, int m, int xpos, int ypos) {
	char color = board[xpos][ypos];
	for (int c = ypos; c < m; c++) {
		if (board[xpos][c] == '.') continue;
		if (board[xpos][c] == 'O') {
			board[xpos][ypos] = '.';
			return make_pair(xpos, c);
		}
		if (board[xpos][c] == '#' || (board[xpos][c] != '.' && board[xpos][c] != color)) {
			board[xpos][ypos] = '.';
			board[xpos][c - 1] = color;
			return make_pair(xpos, c - 1);
		}
	}
	cout << "Move right error\n";
}

void update_board(vector<string>& board, int n, int m, int dir, int& xpos, int& ypos) {

	pair<int, int> npos;
	// 상(0), 하(1), 좌(2), 우(3)
	switch (dir) {
	case 0:
		npos = move_up(board, n, m, xpos, ypos);
		xpos = npos.first;
		ypos = npos.second;
		break;
	case 1:
		npos = move_down(board, n, m, xpos, ypos);
		xpos = npos.first;
		ypos = npos.second;
		break;
	case 2:
		npos = move_left(board, n, m, xpos, ypos);
		xpos = npos.first;
		ypos = npos.second;
		break;
	case 3:
		npos = move_right(board, n, m, xpos, ypos);
		xpos = npos.first;
		ypos = npos.second;
		break;
	}
}

void move_board_proc(vector<string>& board, int n, int m, int& rxpos, int& rypos, int& bxpos, int& bypos, int cnt, int& ans) {
	// 기저사례1
	// 파란 구슬이 빠진 경우 (빨간 구슬과 파란 구슬이 동시에 빠져도 실패이므로 먼저 체크해야함)
	if (check_hole(board, bxpos, bypos)) return;
	// 기저사례2: 빨간 구슬이 빠진 경우
	if (check_hole(board, rxpos, rypos)) {
		if (ans > cnt) ans = cnt;
		return;
	}
	// 기저사례3: 10번을 초과하여 기울인 경우
	if (cnt == 10) return;

	for (int dir = 0; dir < 4; dir++) {
		vector<string> cur_board = board; // 기울이기 전 보드
		int c_rxpos = rxpos, c_rypos = rypos, c_bxpos = bxpos, c_bypos = bypos;
		int prior = set_priority_ball(dir, rxpos, rypos, bxpos, bypos);
		if (prior == 0) {
			update_board(board, n, m, dir, rxpos, rypos);
			update_board(board, n, m, dir, bxpos, bypos);
		}
		else {
			update_board(board, n, m, dir, bxpos, bypos);
			update_board(board, n, m, dir, rxpos, rypos);
		}
		move_board_proc(board, n, m, rxpos, rypos, bxpos, bypos, cnt + 1, ans);
		board = cur_board;
		rxpos = c_rxpos, rypos = c_rypos, bxpos = c_bxpos, bypos = c_bypos;
	}
}

// Debugging
void print_board(vector<string>& board) {
	for (auto ele : board)
		cout << ele << endl;
	cout << endl;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;

	vector<string> board;
	string str;
	for (int line = 0; line < n; line++) {
		cin >> str;
		board.push_back(str);
	}

	int rxpos, rypos, bxpos, bypos;
	int ans = 100;
	find_red_blue_pos(board, rxpos, rypos, bxpos, bypos);
	move_board_proc(board, n, m, rxpos, rypos, bxpos, bypos, 0, ans);
	if (ans > 10)
		ans = -1;
	cout << ans << endl;
}