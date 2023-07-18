#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cctype>

using namespace std;

bool cmp(pair<int, int> p1, pair<int, int> p2){
    return p1.second > p2.second;
}

vector<int> solution(string s) {
    vector<int> answer;
    
    string str;
    map<int, int> table;
    for(int i=0; i<s.length(); i++){
        if(isdigit(s[i])) str.push_back(s[i]);
        else if(str.size()>0){
            int ele = stoi(str);
            str.clear();
            if(table.find(ele)==table.end())
                table[ele] = 0;
            else
                table[ele] += 1;
        }
    }
    vector<pair<int, int>> v(table.begin(), table.end());
    sort(v.begin(), v.end(), cmp);
    for(int i=0; i<v.size(); i++)
        answer.push_back(v[i].first);
    
    return answer;
}