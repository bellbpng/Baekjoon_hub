#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

bool checkValidString(string str) {
	stack<char> s;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == '[') s.push(str[i]);
		else {
			if (s.size() == 0) return false;
			if (str[i] == ')' && s.top() != '(') return false;
			else if (str[i] == ']' && s.top() != '[') return false;
			else {
				s.pop();
			}
		}
	}
	if (s.size() != 0) return false;
	return true;
}

// 제거되지 못한 괄호 값을 곱해준다.
int remainStackValue(stack<char> s) {
	int ret = 1;
	while (!s.empty()) {
		if (s.top() == '(') ret *= 2;
		else if (s.top() == '[') ret *= 3;
		s.pop();
	}
	return ret;
}

// 분배법칙이 적용된 계산 로직
int getValue(string str) {
	stack<char> s;
	int ans = 0;
	int tmp = 1;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '(' || str[i] == '[') s.push(str[i]);
		else if (str[i] == ')' || str[i]==']') {
			if (str[i] == ')') tmp *= 2;
			else if (str[i] == ']') tmp *= 3;
			s.pop();
			if (i + 1 < str.length()) { 
				// 오른쪽 괄호 다음이 왼쪽 괄호인 경우 값을 더한다.
				if (str[i + 1] == '(' || str[i + 1] == '[') {
					tmp *= remainStackValue(s);
					ans += tmp;
					tmp = 1;
				}
			}
		}
	}
	ans += tmp;
	return ans;
}

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);
	string str;
	cin >> str;

	// 올바른 문자열인지 확인
	bool flag = checkValidString(str);
	if (flag == 0) {
		printf("0\n");
		return 0;
	}
	
	int ans = getValue(str);
	printf("%d\n", ans);
	
	return 0;
}