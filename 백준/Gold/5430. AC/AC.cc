#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <deque>
using namespace std;

int dir; // 0: 정방향, 1: 역방향

int functionD(deque<int>& dq) {
	if (dq.size() == 0) return -1;

	if (dir == 0) dq.pop_front();
	else dq.pop_back();

	return 1;
}

void command(string p, deque<int>& dq) {
	for (int i = 0; i < p.size(); i++) {
		if (p[i] == 'R') {
			dir = ~dir; // not 연산
		}
		else if (p[i] == 'D') {
			if (functionD(dq) == -1) {
				printf("error\n");
				return;
			}
		}
	}

	printf("[");
	if (dir == 0) {
		for (int i = 0; i < dq.size(); i++) {
			if (i == dq.size() - 1) printf("%d", dq[i]);
			else printf("%d,", dq[i]);
		}
	}
	else {
		for (int i = dq.size() - 1; i >= 0; i--) {
			if (i == 0) printf("%d", dq[i]);
			else printf("%d,", dq[i]);
		}
	}
	printf("]\n");
}

string getRealP(string p) {
	string ret;
	int cnt = 0;
	for (int i = 0; i < p.length(); i++) {
		if (p[i] == 'R') {
			cnt++;
		}
		else if (p[i] == 'D') {
			if (cnt == 0) {
				ret.push_back(p[i]);
				continue;
			}
			if (cnt % 2 == 1) ret.push_back('R');
			ret.push_back(p[i]);
			cnt = 0;
		}
	}
	if (cnt > 0 && cnt % 2 == 1) 
		ret.push_back('R');

	return ret;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int testCase = 0; testCase < T; testCase++) {
		dir = 0;
		string p;
		cin >> p;
		p = getRealP(p);
		int n; 
		cin >> n; getchar();
		string origin, numArr;
		cin >> origin;
		for (int i = 0; i < origin.size(); i++) {
			if (origin[i] == '[' || origin[i] == ']') continue;
			numArr.push_back(origin[i]);
		}
		deque<int> dq;
		stringstream ss(numArr);
		string token;
		int num;
		while (getline(ss,token, ',')) {
			num = stoi(token);
			dq.push_back(num);
		}
		command(p, dq);
	}
	return 0;
}