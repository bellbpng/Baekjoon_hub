#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> matrix_mul(vector<vector<int>>& front_mat, vector<vector<int>>& back_mat)
{
	int n = front_mat[0].size();
	vector<vector<int>> rmat(n, vector<int>(n,0));

	for(int r=0; r<n; r++) {
		for(int c=0; c<n; c++) {
			int ele=0;
			for(int i=0; i<n; i++) {
				ele += front_mat[r][i]*back_mat[i][c];
			}
			rmat[r][c] = ele%1000;
		}
	}
	return rmat;
}

void print_matrix(vector<vector<int>>& mat)
{
	int n = mat[0].size();
	for(int r=0; r<n; r++) {
		for(int c=0; c<n; c++)
			cout << mat[r][c] << " ";
		cout << endl;
	}
}

void pow_matrix(vector<vector<int>>& front_mat, vector<vector<int>>& back_mat, long long B)
{	
	// B가 1인 경우 그대로 출력
	if(B==1) {
		print_matrix(front_mat);
		return;
	}
	int n = front_mat[0].size();
	vector<vector<int>> ans_mat(n, vector<int>(n,0));

	while(B>=2) {
		if(B%2==0) { // 짝수인 경우 
			back_mat = matrix_mul(front_mat, back_mat);
			front_mat = matrix_mul(front_mat, front_mat);
		}	
		else { // 홀수인 경우
			front_mat = matrix_mul(front_mat, front_mat);
			back_mat = matrix_mul(front_mat, back_mat);
		}
		ans_mat = back_mat;
		B/=2;
	}	
	print_matrix(ans_mat);
}

int main()
{
	int N;
	long long B;
	cin >> N >> B;

	vector<vector<int>> front_matrix(N,vector<int>(N,0));
	vector<vector<int>> back_matrix(N,vector<int>(N,0));

	for(int r=0; r<N; r++)
		for(int c=0; c<N; c++) {
			int val;
			cin >> val;
			front_matrix[r][c] = val%1000;
		}
			

	back_matrix = front_matrix;
	pow_matrix(front_matrix, back_matrix, B);
	return 0;
}