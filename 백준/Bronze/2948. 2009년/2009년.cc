#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int d, m;
	cin >> d >> m;
	// 각 달의 일수
	vector<int> month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	vector<string> days = { "Thursday", "Friday", "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday" };
	
	// 1월 1일을 기준으로 날수를 계산
	int diff_month = m - 1;
	int diff_day = d - 1;
	for (int i = 0; i < diff_month; i++) {
		diff_day += month[i];
	}
	cout << days[diff_day % 7] << endl;
	return 0;
}