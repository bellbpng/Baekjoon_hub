#include <string>
#include <vector>
#include <cctype>
#include <map>
#include <algorithm>

using namespace std;

int solution(string s) {
    int answer = 0;
    
    // init
    string result;
    map<string, char> table;
    table["zero"] = '0'; table["one"] = '1';
    table["two"] = '2'; table["three"] = '3';
    table["four"] = '4'; table["five"] = '5';
    table["six"] = '6'; table["seven"] = '7';
    table["eight"] = '8'; table["nine"] = '9';
    
    string tmp;
    for(int i=0; i<s.length(); i++){
        if(isdigit(s[i])){
            result.push_back(s[i]);
        }
        else{ // 알파벳인 경우
            tmp.push_back(s[i]);
            if(table.find(tmp)==table.end()) continue;
            result.push_back(table[tmp]);
            tmp.clear();
        }
    }
    
    answer = stoi(result);
    
    return answer;
}