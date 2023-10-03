#include <iostream>
#include <string>
#include <vector>
#include <memory.h>
#include <cctype>
#include <queue>
using namespace std;

vector<string> board, answer;
vector<char> cand[9][9];
vector<pair<int, int>> node;

void setCand(int x, int y) {
	int digit[10];
	memset(digit, 0, sizeof(digit));

	// check row
	for (int c = 0; c < 9; c++) {
		if (c == y) continue;
		digit[board[x][c] - '0'] = 1;
	}

	// check col
	for (int r = 0; r < 9; r++) {
		if (r == x) continue;
		digit[board[r][y] - '0'] = 1;
	}

	// check box
	int sx = (x / 3) * 3;
	int sy = (y / 3) * 3;
	for (int dx = 0; dx < 3; dx++) {
		for (int dy = 0; dy < 3; dy++) {
			if ((sx + dx == x) && (sy + dy == y)) continue;
			digit[board[sx + dx][sy + dy] - '0'] = 1;
		}
	}

	// set cand
	for (int i = 1; i <= 9; i++) {
		if (digit[i] == 0) cand[x][y].push_back(i+'0');
	}
}

void printAnswer() {
	for (auto ele : answer) {
		cout << ele << "\n";
	}
}

bool checkRow(int x, int y, char ele) {
	for (int c = 0; c < 9; c++) {
		if (c == y) continue;
		if (ele == board[x][c]) return true;
	}
	return false;
}

bool checkCol(int x, int y, char ele) {
	for (int r = 0; r < 9; r++) {
		if (r == x) continue;
		if (ele == board[r][y]) return true;
	}
	return false;
}

bool checkBox(int x, int y, char ele) {
	int sx = (x / 3) * 3;
	int sy = (y / 3) * 3;
	for (int dx = 0; dx < 3; dx++) {
		for (int dy = 0; dy < 3; dy++) {
			if ((sx + dx == x) && (sy + dy == y)) continue;
			if (board[sx + dx][sy + dy] == ele) return true;
		}
	}
	return false;
}

void playSdoku(int v) {
	if (v == node.size()) {
		answer = board;
		printAnswer();
		exit(0);
	}

	int xpos = node[v].first;
	int ypos = node[v].second;
	for (auto ele : cand[xpos][ypos]) {
		if (checkRow(xpos, ypos, ele) || checkCol(xpos, ypos, ele) || checkBox(xpos, ypos, ele)) continue;
		board[xpos][ypos] = ele;
		playSdoku(v + 1);
		board[xpos][ypos] = '0';
	}

}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	for (int i = 0; i < 9; i++) {
		string str;
		cin >> str;
		board.push_back(str);
	}

	// 빈칸과 후보 숫자 정하기
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			if (board[r][c] == '0') {
				setCand(r, c);
			}
		}
	}
	// set node
	for (int r = 0; r < 9; r++) {
		for (int c = 0; c < 9; c++) {
			if (cand[r][c].size() == 0) continue;
			node.push_back(make_pair(r, c));
		}
	}
	playSdoku(0);
	printAnswer();

	return 0;
}