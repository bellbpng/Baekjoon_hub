#include <iostream>
#include <string>
using namespace std;

int main()
{
	string str;
	getline(cin, str);

	int happy = 0, sad = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ':' && str[i+1]=='-' && str[i+2]==')') {
			happy++;
			i += 2;
		}
		else if (str[i] == ':' && str[i + 1] == '-' && str[i + 2] == '(') {
			sad++;
			i += 2;
		}
	}
	if (happy == 0 && sad == 0) cout << "none" << endl;
	else if (happy > sad) cout << "happy" << endl;
	else if (happy == sad) cout << "unsure" << endl;
	else cout << "sad" << endl;
}