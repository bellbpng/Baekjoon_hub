#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N;

// NxN 행렬곱 연산 함수
vector<vector<int>> matrix_mul(vector<vector<int>>& front_matrix, vector<vector<int>>& back_matrix)
{
	vector<int> row, col;
	vector<vector<int>> new_matrix(N, vector<int>(N));
	for (int r = 0; r < N; r++)
	{
		// r행에 해당하는 원소를 담는다.
		for (int c = 0; c < N; c++)
			row.push_back(front_matrix[r][c]);
		
		// 행렬곱을 통해 원소 값을 계산한다.
		for (int c = 0; c < N; c++)
		{
			// row 원소와 곱할 열 원소를 담는다.
			for (int r = 0; r < N; r++)
				col.push_back(back_matrix[r][c]);
			// row 원소와 col 원소를 곱한다.
			int ele = 0;
			for (int i = 0; i < N; i++)
				ele += row[i] * col[i];
			new_matrix[r][c] = ele % 1000;
			col.clear();
		}
		row.clear();
	}
	return new_matrix;
}

bool check_matrix(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2)
{
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			if (matrix1[r][c] != matrix2[r][c])
				return false;
	return true;
}

void matrix_b_square(vector<vector<int>>& front_matrix, vector<vector<int>>& back_matrix, long long b)
{
	// 남은 곱셈 횟수(b)가 짝수인 경우
	if (b % 2 == 0)
	{
		if (check_matrix(front_matrix, back_matrix)) // front_matrix와 back_matrix가 같은 경우
		{
			front_matrix = matrix_mul(front_matrix, front_matrix);
			back_matrix = front_matrix;
		}
		else
		{
			back_matrix = matrix_mul(front_matrix, back_matrix);
			front_matrix = matrix_mul(front_matrix, front_matrix);
		}
	}
	else // 남은 곱셈 횟수(b)가 홀수인 경우
	{
		front_matrix = matrix_mul(front_matrix, front_matrix);
		back_matrix = matrix_mul(front_matrix, back_matrix);
	}
}

void print_matrix(vector<vector<int>>& matrix)
{
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++)
			cout << matrix[r][c] << " ";
		cout << endl;
	}
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	long long B;
	cin >> N >> B;
	vector<vector<int>> matrix(N, vector<int>(N));
	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
		{
			int val;
			cin >> val;
			matrix[r][c] = val%1000;
		}

	vector<vector<int>> front_matrix = matrix;
	vector<vector<int>> back_matrix = matrix;
	vector<vector<int>> ans_matrix = matrix_mul(front_matrix, back_matrix);

	while (true)
	{
		if (B == 1)
		{
			ans_matrix = front_matrix;
			break;
		}
		if (B == 2)
		{
			ans_matrix = matrix_mul(front_matrix, back_matrix);
			break;
		}
		matrix_b_square(front_matrix, back_matrix, B);
		if (B == 3)
		{
			ans_matrix = back_matrix;
			break;
		}
		B /= 2;
	}
	print_matrix(ans_matrix);
	return 0;
}