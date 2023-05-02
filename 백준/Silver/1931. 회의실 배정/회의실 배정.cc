#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct _meet
{
	int start;
	int end;
} Meet;

int N;
vector<Meet> v;

bool cmp(Meet m1, Meet m2)
{
	if (m1.end != m2.end)
		return m1.end < m2.end;
	else if (m1.end == m2.end)
		return m1.start < m2.start;
}

int proc()
{
	int count = 1; // 처음에 회의는 하나
	int end_time = v[0].end;

	for (int i = 1; i < v.size(); i++)
	{
		if (end_time <= v[i].start)
		{
			end_time = v[i].end;
			count++;
		}
	}

	return count;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	cin >> N;
	Meet tmp;
	for (int i = 0; i < N; i++)
	{
		cin >> tmp.start >> tmp.end;
		v.push_back(tmp);
	}

	sort(v.begin(), v.end(), cmp); // N개의 회의
	int ans = proc();

	cout << ans << endl;
	return 0;

}