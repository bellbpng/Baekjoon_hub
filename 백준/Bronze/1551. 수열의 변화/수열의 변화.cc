#include <iostream>
#include <vector>
#include <string>
using namespace std;

// 주어진 배열에서 인접한 두 원소의 차이를 이용해 크기가 1 줄어든 새로운 수열을 만든다.
void make_adj_arr(vector<int>& before, int k) {
	//기저사례: k==0
	if (k == 0) {
		for (int i = 0; i < before.size(); i++) {
			cout << before[i];
			if (i < before.size() - 1) cout << ",";
		}
		cout << endl;
		return;
	}

	vector<int> after;
	for (int i = 0; i < before.size() - 1; i++) {
		int val = before[i + 1] - before[i];
		after.push_back(val);
	}
	make_adj_arr(after, k - 1);
}

int main()
{
	int n, k;
	cin >> n >> k;
	string str;
	cin >> str;
	vector<int> before;
	string num;
	for (int i = 0; i < str.size(); i++) {
		num.push_back(str[i]);
		if (str[i] == ',') {
			before.push_back(stoi(num));
			num.clear();
		}
	}
	before.push_back(stoi(num));
	make_adj_arr(before, k);
}