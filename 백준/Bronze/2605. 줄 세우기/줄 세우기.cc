#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<int> sarr(n);
	for (int i = 0; i < n; i++) {
		sarr[i] = i + 1;
		int tmp;
		cin >> tmp;
		int nidx = i - tmp;
		if (nidx < i) {
			for (int idx = i-1; idx >=nidx; idx--) {
				sarr[idx+1] = sarr[idx];
			}
		}
		sarr[nidx] = i + 1;
	}
	for (auto ele : sarr)
		cout << ele << " ";
	cout << endl;
}