#include <iostream>
#include <vector>
using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	scanf("%d", &T);
	vector<int> triNumber;
	for (int n = 1; n <= 50; n++) {
		int val = n * (n + 1) / 2;
		for(int i=0; i<3; i++)
			triNumber.push_back(val);
	}
	int len = triNumber.size();

	for (int testCase = 0; testCase < T; testCase++) {
		int num;
		bool flag = false;
		scanf("%d", &num);
		for (int i = 0; i < len-2; i++) {
			for (int j = i + 1; j < len - 1; j++) {
				for (int k = j + 1; k < len; k++) {
					int val = triNumber[i] + triNumber[j] + triNumber[k];
					if (num == val) {
						printf("1\n");
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
			if (flag) break;
		}
		if (flag == false) printf("0\n");
	}
}