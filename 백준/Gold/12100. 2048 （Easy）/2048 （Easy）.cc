#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void add_block(vector<int>& org_blocks, queue<int>& added_blocks, int& max_val) {
	// add blocks
	for (int i = 0; i < org_blocks.size(); i++) {
		if (i == org_blocks.size() - 1) {
			added_blocks.push(org_blocks[i]);
			break;
		}

		if (org_blocks[i] == org_blocks[i + 1]) {
			org_blocks[i] += org_blocks[i + 1];
			added_blocks.push(org_blocks[i]);
			if (max_val < org_blocks[i]) max_val = org_blocks[i];
			i++;
		}
		else {
			added_blocks.push(org_blocks[i]);
		}
	}
	org_blocks.clear();
}

// 보드 위에 전체 블록을 이동시킨다.
void move_blocks(vector<vector<int>>& board, int dir, int& max_val) {
	int n = board.size();
	vector<vector<int>> nboard(n, vector<int>(n, 0));

	int cnt = 0;
	vector<int> org_blocks;
	queue<int> added_blocks;
	// 상하(0,1)는 각 열에 대해서 블록을 이동시키고, 좌우(2,3)은 각 행에 대해서 블록을 이동시킨다.
	switch (dir) {
	case 0:
		for (int c = 0; c < n; c++) {
			for (int r = 0; r < n; r++) {
				if (board[r][c] != 0)
					org_blocks.push_back(board[r][c]);
			}
			if (org_blocks.empty()) continue;

			add_block(org_blocks, added_blocks, max_val);

			// update nboard
			if (added_blocks.empty()) continue;
			for (int r = 0; r < n; r++) {
				nboard[r][c] = added_blocks.front();
				added_blocks.pop();
				if (added_blocks.empty()) break;
			}
		}
		break;
	case 1:
		for (int c = 0; c < n; c++) {
			for (int r = n-1; r >= 0; r--) {
				if (board[r][c] != 0)
					org_blocks.push_back(board[r][c]);
			}
			if (org_blocks.empty()) continue;

			add_block(org_blocks, added_blocks, max_val);

			// update nboard
			if (added_blocks.empty()) continue;
			for (int r = n - 1; r >= 0; r--) {
				nboard[r][c] = added_blocks.front();
				added_blocks.pop();
				if (added_blocks.empty()) break;
			}
		}
		break;
	case 2:
		for (int r = 0; r < n; r++) {
			for (int c = 0; c < n; c++) {
				if (board[r][c] != 0)
					org_blocks.push_back(board[r][c]);
			}
			if (org_blocks.empty()) continue;

			add_block(org_blocks, added_blocks, max_val);

			// update nboard
			if (added_blocks.empty()) continue;
			for (int c = 0; c < n; c++) {
				nboard[r][c] = added_blocks.front();
				added_blocks.pop();
				if (added_blocks.empty()) break;
			}
		}
		break;
	case 3:
		for (int r = 0; r < n; r++) {
			for (int c = n-1; c >= 0; c--) {
				if (board[r][c] != 0)
					org_blocks.push_back(board[r][c]);
			}
			if (org_blocks.empty()) continue;

			add_block(org_blocks, added_blocks, max_val);

			// update nboard
			if (added_blocks.empty()) continue;
			for (int c = n - 1; c >= 0; c--) {
				nboard[r][c] = added_blocks.front();
				added_blocks.pop();
				if (added_blocks.empty()) break;
			}
		}
		break;
	}
	board = nboard;
}

void print_board(vector<vector<int>>& board, int dir) {
	int n = board.size();

	cout << "dir: " << dir << endl;
	cout << "----------------------------\n";
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++)
			cout << board[r][c] << " ";
		cout << endl;
	}
	cout << endl;
}

// Debugging
void check_move(vector<vector<int>>& board) {
	vector<vector<int>> cur_board = board;
	int tmp_val = 0;
	move_blocks(board, 0, tmp_val);
	print_board(board, 0);

	board = cur_board;
	move_blocks(board, 1, tmp_val);
	print_board(board, 1);

	board = cur_board;
	move_blocks(board, 2, tmp_val);
	print_board(board, 2);

	board = cur_board;
	move_blocks(board, 3, tmp_val);
	print_board(board, 3);
}

void play_game(vector<vector<int>>& board, int& max_val, int n, int cnt) {
	// 기저사례: 보드를 5번 움직인 경우
	if (cnt == 5) return;

	// dir: 상(0), 하(1), 좌(2), 우(3)
	for (int dir = 0; dir < 4; dir++) {
		vector<vector<int>> cur_board = board;
		move_blocks(board, dir, max_val);
		play_game(board, max_val, n, cnt + 1);
		board = cur_board;
	}
}


int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<vector<int>> board(n, vector<int>(n, 0));
	int max_val = 0;
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			cin >> board[r][c];
			if (max_val < board[r][c])
				max_val = board[r][c];
		}
	}

	play_game(board, max_val, n, 0);
	cout << max_val << endl;

	// check_move(board);
	return 0;
}