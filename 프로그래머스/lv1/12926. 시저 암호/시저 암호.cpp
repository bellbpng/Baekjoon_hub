#include <string>
#include <vector>
#include <cctype>

using namespace std;

string solution(string s, int n) {
    string answer = "";
    
    for(int i=0; i<s.length(); i++){
        if(islower(s[i])){
            int diff = s[i] + n - 'z';
            if(diff>0)
                s[i] = 'a' + diff - 1;
            else
                s[i] += n;
        }
        else if(isupper(s[i])){
            int diff = s[i] + n - 'Z';
            if(diff>0)
                s[i] = 'A' + diff - 1;
            else
                s[i] += n;
        }
        answer.push_back(s[i]);
    }
    
    return answer;
}