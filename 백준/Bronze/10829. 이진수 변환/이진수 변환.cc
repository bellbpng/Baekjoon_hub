#include <iostream>
#include <stack>
using namespace std;

int main()
{
	long long N;
	cin >> N;

	stack<int> binary;
	while (true) {
		if (N / 2 == 0) {
			binary.push(1);
			break;
		}
		binary.push(N % 2);
		N /= 2;
	}
	while (!binary.empty()) {
		printf("%d", binary.top());
		binary.pop();
	}
	return 0;
}