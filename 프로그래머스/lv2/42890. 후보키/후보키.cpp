#include <string>
#include <vector>
#include <memory.h>
#include <iostream>
#include <algorithm>
using namespace std;

int answer=0, colNum=0;
vector<string> history;
bool visited[8];
vector<int> cand;

bool checkUnique(vector<vector<string>>& relation){
    vector<vector<string>> table;
    for(int r=0; r<relation.size(); r++){
        vector<string> list;
        for(int i=0; i<cand.size(); i++){
            list.push_back(relation[r][cand[i]]);
        }
        table.push_back(list);
        int tuple = 0;
        for(int i=0; i<table.size(); i++){
            int cnt=0;
            for(int j=0; j<table[i].size(); j++){
                if(list[j]==table[i][j]) cnt++;
            }
            if(cnt == list.size()) tuple++;
        }
        if(tuple>1) return false;
    }
    return true;
}

bool checkMinimality(string combi){
    for(int i=0; i<history.size(); i++){
        int cnt = 0;
        for(int j=0; j<history[i].length(); j++){
            for(int k=0; k<combi.length(); k++){
                if(history[i][j] == combi[k]) cnt++;
            }
        }
        if(cnt == history[i].length()) return false;
    }
    return true;
}

void makeCombination(vector<vector<string>>& relation, int v, int n){
    if(cand.size()==n){
        string str;
        for(int i=0; i<cand.size(); i++){
            str.push_back(cand[i] + '0');
        }
        if(checkUnique(relation) && checkMinimality(str)){
            answer++;
            history.push_back(str);
        }
        return;
    }
    
    for(int i=v; i<colNum; i++){
        if(visited[i]) continue;
        visited[i] = true;
        cand.push_back(i);
        makeCombination(relation, i+1, n);
        visited[i] = false;
        cand.pop_back();
    }
}

int solution(vector<vector<string>> relation) {
    colNum = relation[0].size();
    
    for(int i=1; i<=colNum; i++){
        memset(visited, false, sizeof(visited));
        makeCombination(relation, 0, i);
    }
    
    return answer;
}