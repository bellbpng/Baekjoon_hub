#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>

#define INF 1000000

using namespace std;
// w = table[u].first, v = table[u].second
int N;
vector<pair<int, int>> table[201];
int cost[201];
// s(0), a(1), b(2)
// dList[0][1]~dList[0][200] 은 s부터 각 노드까지의 최소비용
int dList[3][201]; 

void dijkstra(int idx, int start){
    for(int i=1; i<=N; i++){
        dList[idx][i]=INF;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});
    dList[idx][start]=0;
    
    while(!pq.empty()){
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();
        if(dList[idx][u] < w) continue;
        for(int i=0; i<table[u].size(); i++){
            int v = table[u][i].second;
            int x = table[u][i].first;
            if(w+x < dList[idx][v]){
                dList[idx][v] = w+x;
                pq.push(make_pair(w+x, v));
            }
        }
    }
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    int ret = INF;
    N = n;
    for(int i=0; i<fares.size(); i++){
        int u = fares[i][0];
        int v = fares[i][1];
        int w = fares[i][2];
        table[u].push_back(make_pair(w, v));
        table[v].push_back(make_pair(w, u));
    }
    dijkstra(0, s);
    dijkstra(1, a);
    dijkstra(2, b);
    ret = dList[1][s] + dList[2][s];
    for(int i=1; i<=n; i++){
        if(dList[0][i]==INF || dList[1][i]==INF || dList[2][i]==INF) continue;
        ret = min(ret, dList[0][i] + dList[1][i] + dList[2][i]);
    }
    
    return ret;
}