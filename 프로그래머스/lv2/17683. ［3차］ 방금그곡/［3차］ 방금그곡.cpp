#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

typedef struct _music{
    string name;
    int playTime;
    int index;
} Music;

string parsing(Music& imusic, string musicInfo, int index){
    stringstream stm(musicInfo);
    string name, sheet, stime, etime, hour, min;
    int playTime = 0;
    string token;
    int cnt = 0;
    while(getline(stm, token, ',')){
        if(cnt==0) stime = token;
        else if(cnt==1) etime = token;
        else if(cnt==2) name = token;
        else if(cnt==3) sheet = token;
        cnt++;
    }
    
    // get play time
    stm.clear(); stm.str(etime); cnt=0;
    while(getline(stm, token, ':')){
        if(cnt==0) hour = token;
        else if(cnt==1) min = token;
        cnt++;
    }
    playTime = stoi(hour)*60 + stoi(min);
    stm.clear(); stm.str(stime); cnt=0;
    while(getline(stm, token, ':')){
        if(cnt==0) hour = token;
        else if(cnt==1) min = token;
        cnt++;
    }
    playTime -= (stoi(hour)*60+stoi(min));
    
    imusic = {name, playTime, index};
    
    return sheet;
}

string replaceSheet(string sheet){
    string ret;
    for(int i=0; i<sheet.length(); i++){
        if(sheet[i]=='#'){
            char ch = ret.back();
            ret.pop_back();
            ret.push_back(tolower(ch));
        }
        else
            ret.push_back(sheet[i]);
    }
    return ret;
}

bool checkMemory(string m, string sheet, int playTime){
    int len = sheet.length();
    int idx = 0;
    string cstr;
    for(int t=0; t<playTime; t++){
        if(idx==len) idx=0;
        cstr.push_back(sheet[idx++]);
    }
    // cout << cstr << endl;
    if(cstr.find(m)==string::npos) return false;
    return true;
}

bool cmp(Music m1, Music m2){
    if(m1.playTime != m2.playTime)
        return m1.playTime > m2.playTime;
    else
        return m1.index < m2.index;
}

string solution(string m, vector<string> musicinfos) {
    string answer = "";
    
    m = replaceSheet(m);
    // cout << "memory: " << m << endl;
    string sheet;
    Music music;
    vector<Music> cand;
    for(int i=0; i<musicinfos.size(); i++){
        sheet = parsing(music, musicinfos[i], i); // 악보 반환
        sheet = replaceSheet(sheet);
        // cout << sheet << endl;
        if(checkMemory(m, sheet, music.playTime)){
            cand.push_back(music);
        }
    }
    if(cand.size()==0) answer = "(None)";
    else {
        sort(cand.begin(), cand.end(), cmp);
        answer = cand[0].name;
    }
    
    return answer;
}