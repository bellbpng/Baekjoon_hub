#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

string solution(int n, int t, int m, vector<string> timetable) {
    vector<int> crewTable;
    string answer = "";
    stringstream stm;
    int hh, mm;
    for(int i=0; i<timetable.size(); i++){
        stm.clear();
        stm.str(timetable[i]);
        stm >> hh; stm.get(); stm>>mm;
        int time = hh*60 + mm;
        crewTable.push_back(time);
    }
    sort(crewTable.begin(), crewTable.end());
    int busTime = 540;
    int idx=0, cnt=0, time = 0;
    for(int i=0; i<n; i++){
        cnt=0;
        for(int j=idx; j<crewTable.size(); j++){
            if(crewTable[j] > busTime) break;
            cnt++; idx++;
            if(cnt == m) break;
        }
        // 마지막 버스에 몇명이 탔는지만 중요!
        if(i==n-1){
            if(cnt == m)
                time = crewTable[idx-1]-1;
            else
                time = busTime;
        }
        busTime += t;
    }
    
    hh = time/60;
    mm = time%60;
    if(hh<10) answer += "0";
    answer += to_string(hh) + ":";
    if(mm<10) answer += "0";
    answer += to_string(mm);
    
    return answer;
}