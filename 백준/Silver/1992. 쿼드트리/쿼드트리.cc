#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 탐색 영역이 단일 색(0 또는 1)인지, 혼합(2)인지 판단
char check_color(vector<string>& image, int x, int y, int n) {
	char ref = image[x][y];
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			if (image[r+x][c+y] != ref)
				return '2';
		}
	}
	return ref;
}

void compress(vector<string>& image, int x, int y, int size) {
	// 기저사례: 영역이 0으로만 이루어졌거나 1로만 이루어진 경우
	char ref = check_color(image, x, y, size);
	if (ref == '0' || ref=='1') {
		cout << ref;
		return;
	}

	int half = size / 2;
	cout << "(";
	compress(image, x, y, half);
	compress(image, x, y + half, half);
	compress(image, x + half, y, half);
	compress(image, x + half, y + half, half);
	cout << ")";
	return;
}

int main(void)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int N;
	string str;
	vector<string> image;
	cin >> N;
	for (int line = 0; line < N; line++) {
		cin >> str;
		image.push_back(str);
	}
	compress(image, 0, 0, N);
	return 0;
}