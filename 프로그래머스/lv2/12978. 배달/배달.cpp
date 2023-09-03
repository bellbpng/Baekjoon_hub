#include <iostream>
#include <vector>
#include <queue>
#include <memory.h>

#define INF 9e8
using namespace std;

// c = table[u].first, v = table[u].second
// u->v 로 가는 비용 c를 표현
vector<pair<int, int>> table[51]; 
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int dist[51];

void dijkstra(int start){
    dist[start]=0;
    pq.push(make_pair(0, start));
    
    while(!pq.empty()){
        int u = pq.top().second;
        int c = pq.top().first;
        pq.pop();
        
        for(int i=0; i<table[u].size(); i++){
            int v = table[u][i].second;
            int x = table[u][i].first;
            if(dist[v] > c+x){
                dist[v] = c+x;
                pq.push(make_pair(c+x,v));
            }
        }
    }
    
}


int solution(int N, vector<vector<int> > road, int K) {
    int answer = 0;

    for(int i=0; i<road.size(); i++){
        int from = road[i][0];
        int to = road[i][1];
        int cost = road[i][2];
        table[from].push_back(make_pair(cost, to));
        table[to].push_back(make_pair(cost, from));
    }  
    memset(dist, 0, sizeof(dist));
    for(int i=1; i<=N; i++){
        dist[i] = INF;
    }
    dijkstra(1);
    for(int i=1; i<=N; i++){
        // cout << dist[i] << " ";
        if(dist[i]<=K) answer++;
    }
    
    return answer;
}