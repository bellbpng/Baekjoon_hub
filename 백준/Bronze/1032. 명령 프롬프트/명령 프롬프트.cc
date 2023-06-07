#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<string> sarr(n);
	for (int i = 0; i < n; i++) {
		cin >> sarr[i];
	}

	for (int i = 0; i < sarr[0].size(); i++) {
		bool flag = false;
		for (int num = 0; num < n-1; num++) {
			if (sarr[num][i] != sarr[num + 1][i]) {
				cout << "?";
				flag = true;
				break;
			}
		}
		if (flag) continue;
		cout << sarr[0][i];
	}
	cout << endl;
	return 0;
}