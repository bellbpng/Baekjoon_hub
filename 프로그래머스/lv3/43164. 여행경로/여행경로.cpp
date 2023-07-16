#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

bool flag = false;

// 오름차순 정렬
bool cmp(vector<string> v1, vector<string> v2){
    if(v1[0]!=v2[0]) return v1[0] < v2[0];
    else return v1[1] < v2[1];
}

void set_route(vector<vector<string>>& tickets, vector<bool>& visited, vector<string>& answer, string airport, int cnt){
    // 기저사례: 모든 티켓을 방문한 경우
    if(cnt==tickets.size()){
        flag = true;
        answer.push_back(airport); // 마지막 도착지
        return;
    }
    
    answer.push_back(airport);
    for(int i=0; i<tickets.size(); i++){
        if(!visited[i] && tickets[i][0]==airport) { // 티켓 고르기
            visited[i] = true;
            set_route(tickets, visited, answer, tickets[i][1], cnt+1);
            if(flag==false){ // 모든 티켓을 방문하지 못한 경우
                answer.pop_back();
                visited[i]=false;
            }
        }
    }
}

vector<string> solution(vector<vector<string>> tickets) {
    vector<string> answer;
    
    // init
    sort(tickets.begin(), tickets.end(), cmp);
    
    // dfs
    vector<bool> visited(tickets.size(), false);
    set_route(tickets, visited, answer, "ICN", 0);
    return answer;
}