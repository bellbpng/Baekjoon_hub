#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	vector<int> alpha_cnt(26, 0);
	
	while (true) {
		string str;
		cin >> str;
		if (cin.eof() == true) break;
		for (int i = 0; i < str.size(); i++) {
			if(isalpha(str[i]))
				alpha_cnt[str[i]-'a']++;
		}
	}
	int max = *max_element(alpha_cnt.begin(), alpha_cnt.end());
	for (int i = 0; i < 26; i++) {
		if (max == alpha_cnt[i])
			printf("%c", i + 'a');
	}
	cout << endl;
}