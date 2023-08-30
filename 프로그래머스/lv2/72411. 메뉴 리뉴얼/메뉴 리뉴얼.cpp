#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

bool cmp(pair<string, int> p1, pair<string, int> p2){
    return p1.second > p2.second;    
}

void findCombo(map<string, int>& dict, int v, string str, string& menu, int length){
    if(menu.size()==length){
        // cout << menu << endl;
        if(dict.find(menu)==dict.end()) dict[menu]=1;
        else dict[menu]++;
        return;
    }
    
    for(int i=v; i<str.size(); i++){
        menu.push_back(str[i]);
        findCombo(dict, i+1, str, menu, length);
        menu.pop_back();
    }
}

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    vector<int> count(11, 0); // 메뉴 길이별로 몇개 있는지 확인
    for(int i=0; i<orders.size(); i++){
        sort(orders[i].begin(), orders[i].end());
        int len = orders[i].length();
        for(int j=1; j<=len; j++){
            count[j]++;
        }
    }
    
    map<string, int> dict;
    for(int i=0; i<course.size(); i++){
        int comboNum = course[i];
        if(count[comboNum]<2) continue;
        for(int j=0; j<orders.size(); j++){
            if(orders[j].length() < comboNum) continue;
            string menu;
            findCombo(dict, 0, orders[j], menu, comboNum);
        }
    }
    
    vector<pair<string, int>> cand[11];
    for(auto ele:dict){
        int len = ele.first.length();
        if(ele.second<2) continue;
        cand[len].push_back(make_pair(ele.first, ele.second));
    }
    for(int i=0; i<course.size(); i++){
        sort(cand[course[i]].begin(), cand[course[i]].end(), cmp);
    }
    
    // set answer
    for(int i=0; i<course.size(); i++){
        int len = course[i];
        if(cand[len].size()==0) continue;
        int max = cand[len][0].second;
        answer.push_back(cand[len][0].first);
        for(int j=1; j<cand[len].size(); j++){
            if(max == cand[len][j].second)
                answer.push_back(cand[len][j].first);
            else break;
        }
    }
    
    sort(answer.begin(), answer.end());
    return answer;
}