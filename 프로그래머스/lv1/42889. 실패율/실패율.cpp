#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

bool cmp(pair<int, double> p1, pair<int, double> p2){
    if(p1.second != p2.second)
        return p1.second > p2.second;
    else if(p1.second == p2.second)
        return p1.first < p2.first;
}

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    // stage 별로 사용자 수 계산 (1~N+1)
    vector<int> players_on_stage(N+2,0);
    for(int i=0; i<stages.size(); i++){
        players_on_stage[stages[i]]++;
    }
    // stage에 도달한 플레이어 수 계산을 위한 부분합
    vector<int> partial_sum(N+2,0);
    partial_sum[1] = players_on_stage[1];
    for(int i=2; i<=N+1; i++){
        partial_sum[i] = partial_sum[i-1] + players_on_stage[i];
    }
    
    vector<pair<int, double>> failures(N+2);
    for(int i=1; i<=N; i++){
        failures[i].first = i;
        if(players_on_stage[i]==0) 
            failures[i].second = 0.0;
        else
            failures[i].second = (double)players_on_stage[i] / (partial_sum[N+1] - partial_sum[i-1]);
    }
    sort(failures.begin()+1, failures.end()-1, cmp);
    for(int i=1; i<=N; i++){
        answer.push_back(failures[i].first);
    }
    
    return answer;
}