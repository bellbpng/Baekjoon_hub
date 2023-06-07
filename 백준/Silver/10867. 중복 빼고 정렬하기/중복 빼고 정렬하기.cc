#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const int& a, const int& b) {
	return a < b;
}
int main()
{
	int n;
	cin >> n;

	vector<int> v(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];

	sort(v.begin(), v.end(), cmp);
	vector<int> ans;
	for (auto ele : v) {
		if (ans.empty()) ans.push_back(ele);
		if (ans.back() != ele) ans.push_back(ele);
	}
	for (auto ele : ans) {
		cout << ele << " ";
	}
	cout << endl;
	return 0;
}