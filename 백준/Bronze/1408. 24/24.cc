#include <iostream>
#include <string>
using namespace std;

int main(void)
{
	int chour, cmin, csec;
	int shour, smin, ssec;
	scanf("%d:%d:%d", &chour, &cmin, &csec);
	scanf("%d:%d:%d", &shour, &smin, &ssec);

	int rsec = ssec - csec;
	if (rsec < 0) {
		smin--;
		rsec += 60;
	}
	int rmin = smin - cmin;
	if (rmin < 0) {
		shour--;
		rmin += 60;
	}
	int rhour = shour - chour;
	if (rhour < 0)
		rhour += 24;
	
	string sec = to_string(rsec);
	string min = to_string(rmin);
	string hour = to_string(rhour);
	if (rsec < 10) sec = string("0") + sec;
	if (rmin < 10) min = string("0") + min;
	if (rhour < 10) hour = string("0") + hour;
	
	cout << hour << ":" << min << ":" << sec <<  endl;
	return 0;
}