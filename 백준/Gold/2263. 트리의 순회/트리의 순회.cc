#include <iostream>
#include <vector>
using namespace std;

// inorder의 root 인덱스를 반환한다.
// 매개변수 start, end를 모두 포함하는 범위를 탐색한다.
int find_root_inorder(vector<int>&inorder, int start, int end, int root) {
	for (int idx = start; idx <= end; idx++) {
		if (root == inorder[idx])
			return idx;
	}
}

void find_preorder(vector<int>& inorder, vector<int>& postorder, int p_start_idx, int p_end_idx, int i_start_idx, int i_end_idx) {
	// root 출력
	cout << postorder[p_end_idx] << " ";
	// 기저사례: postorder 구간 길이가 1인 경우
	if (i_start_idx == i_end_idx) return;

	// index 정리
	int i_root_idx = find_root_inorder(inorder, i_start_idx, i_end_idx, postorder[p_end_idx]);
	int i_left_start_idx = i_start_idx;
	int i_left_end_idx = i_root_idx - 1;
	int left_size = i_left_end_idx - i_left_start_idx + 1;

	int i_right_start_idx = i_root_idx + 1;
	int i_right_end_idx = i_end_idx;
	int right_size = i_right_end_idx - i_right_start_idx + 1;

	int p_left_start_idx = p_start_idx;
	int p_left_end_idx = p_left_start_idx + left_size - 1;
	int p_right_start_idx = p_left_end_idx + 1;
	int p_right_end_idx = p_end_idx - 1;

	// Left tree
	if(left_size>0)
		find_preorder(inorder, postorder, p_left_start_idx, p_left_end_idx, i_left_start_idx, i_left_end_idx);
	// Right tree
	if(right_size>0)
		find_preorder(inorder, postorder, p_right_start_idx, p_right_end_idx, i_right_start_idx, i_right_end_idx);

	return;
}

int main(void)
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> inorder(n,0);
	vector<int> postorder(n,0);

	for (int i = 0; i < n; i++)
		cin >> inorder[i];
	for (int i = 0; i < n; i++)
		cin >> postorder[i];

	find_preorder(inorder, postorder, 0, n - 1, 0, n - 1);
	return 0;
}